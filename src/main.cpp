/*
 * Smart RV Sail Switch - ATtiny85 Firmware
 *
 * Intelligent sail switch bypass for RV furnaces at high altitude.
 * Uses MPXV5004DP differential pressure sensor to detect blower airflow
 * and provides backup closure signal when original sail switch fails.
 *
 * SAFETY: This operates in parallel with original sail switch (hybrid mode).
 * System starts OPEN (safe), closes relay ONLY when airflow confirmed.
 *
 * Pin Configuration:
 * - PB0 (Arduino 0): Green LED - Active/bypass indicator
 * - PB1 (Arduino 1): Red LED - Idle/error indicator
 * - PB2 (ADC1): MPXV5004DP sensor output (analog) - use analogRead(1)
 * - PB3 (Arduino 3): Sail sense input - monitors original sail switch state
 * - PB4 (Arduino 4): Relay control output - HIGH to close (bypass sail)
 * - PB5: RESET pin (not used as GPIO)
 *
 * Operation:
 * - Continuously monitors pressure sensor for airflow detection
 * - No blower sense wire needed - uses pressure-based detection
 * - Activates relay when airflow detected AND sail switch is open (failed)
 * - Times out and enters error state if no airflow detected
 *
 * Wokwi Simulation Notes:
 * - Remove "frequency" attribute from diagram.json (breaks delay())
 * - Use analogRead(1) for PB2, NOT analogRead(2)
 * - Sail switch needs pull-down resistor
 *
 * License: CC BY-NC-SA 4.0 - See LICENSE file
 * Repository: https://github.com/miclip/smart-rv-sail-switch
 */
#include <Arduino.h>

// Pin definitions
const int SAIL_SENSE_PIN = 3;   // PB3 - Input: HIGH when original sail closed
const int RELAY_PIN = 4;        // PB4 - Output: HIGH to close relay (bypass sail)
const int IDLE_LED = 1;         // PB1 - Output: Red LED for idle/error
const int ACTIVE_LED = 0;       // PB0 - Output: Green LED when bypassing
const int SENSOR_PIN = 1;       // analogRead(1) for PB2 sensor (Wokwi)

// Tunable parameters
const int PRESSURE_THRESHOLD = 100;   // ADC counts above baseline to detect airflow
const int PRESSURE_HYSTERESIS = 50;   // ADC counts below threshold to detect airflow loss
const int DEBOUNCE_CHECKS = 3;        // Consecutive readings needed for detection
const int ERROR_TIMEOUT_MS = 30000;   // 30 seconds without airflow = error state
const int LOOP_DELAY_MS = 100;        // Main loop delay

// Global variables
uint16_t baselineADC = 0;
bool airflowActive = false;
int consecutiveDetections = 0;
int consecutiveLosses = 0;
unsigned long lastAirflowTime = 0;

// Read averaged sensor value (reduces noise)
uint16_t readSensorAveraged() {
  uint32_t sum = 0;
  for (uint8_t i = 0; i < 8; i++) {
    sum += analogRead(SENSOR_PIN);
    delay(1);
  }
  return sum >> 3;  // Divide by 8 using bit shift
}

void setup() {
  // Configure pins
  pinMode(SAIL_SENSE_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(IDLE_LED, OUTPUT);
  pinMode(ACTIVE_LED, OUTPUT);

  // Initialize to safe state - relay open, red LED on
  digitalWrite(RELAY_PIN, LOW);   // Relay open (safe)
  digitalWrite(IDLE_LED, HIGH);   // Red LED on (idle)
  digitalWrite(ACTIVE_LED, LOW);  // Green LED off

  delay(500);

  // Calibrate baseline pressure using averaging
  baselineADC = readSensorAveraged();

  // Sanity check - sensor should read between 50-900 at rest
  if (baselineADC < 50 || baselineADC > 900) {
    // Error mode - rapid blink red LED
    while (true) {
      digitalWrite(IDLE_LED, !digitalRead(IDLE_LED));
      delay(250);
    }
  }

  // Blink 3 times to show calibration success
  for (int i = 0; i < 3; i++) {
    digitalWrite(IDLE_LED, LOW);
    delay(100);
    digitalWrite(IDLE_LED, HIGH);
    delay(100);
  }

  // Initialize timing
  lastAirflowTime = millis();
}

void loop() {
  // Read current pressure
  uint16_t currentADC = readSensorAveraged();
  int16_t pressureDelta = currentADC - baselineADC;

  // Detect airflow onset (with debounce)
  if (!airflowActive && pressureDelta > PRESSURE_THRESHOLD) {
    consecutiveDetections++;
    consecutiveLosses = 0;
    if (consecutiveDetections >= DEBOUNCE_CHECKS) {
      airflowActive = true;
      lastAirflowTime = millis();
      // Quick flash to indicate detection
      digitalWrite(ACTIVE_LED, HIGH);
      delay(200);
      digitalWrite(ACTIVE_LED, LOW);
    }
  }
  // Detect airflow loss (with hysteresis and debounce)
  else if (airflowActive && pressureDelta < (PRESSURE_THRESHOLD - PRESSURE_HYSTERESIS)) {
    consecutiveLosses++;
    consecutiveDetections = 0;
    if (consecutiveLosses >= DEBOUNCE_CHECKS) {
      airflowActive = false;
    }
  }
  // Reset counters if in stable state
  else {
    if (airflowActive) {
      consecutiveLosses = 0;
      lastAirflowTime = millis();
    } else {
      consecutiveDetections = 0;
    }
  }

  // Control relay and LEDs based on state
  if (airflowActive) {
    // Airflow detected - turn off idle LED
    digitalWrite(IDLE_LED, LOW);

    // Hybrid mode: only bypass if sail switch is open (failed)
    if (digitalRead(SAIL_SENSE_PIN) == LOW) {
      digitalWrite(RELAY_PIN, HIGH);    // Close relay (bypass)
      digitalWrite(ACTIVE_LED, HIGH);   // Green LED on
    } else {
      digitalWrite(RELAY_PIN, LOW);     // Relay open (sail switch working)
      digitalWrite(ACTIVE_LED, LOW);    // Green LED off
    }
  } else {
    // No airflow - idle state
    digitalWrite(RELAY_PIN, LOW);       // Relay open (safe)
    digitalWrite(ACTIVE_LED, LOW);      // Green LED off
    digitalWrite(IDLE_LED, HIGH);       // Red LED on (idle)

    // Check for timeout error (no airflow for too long after initial calibration)
    // Only trigger if we've been running for a while and never seen airflow
    if (millis() - lastAirflowTime > ERROR_TIMEOUT_MS && millis() > ERROR_TIMEOUT_MS) {
      // Error state - rapid blink red LED
      while (true) {
        digitalWrite(IDLE_LED, !digitalRead(IDLE_LED));
        delay(250);

        // Check if airflow returns - allow recovery
        currentADC = readSensorAveraged();
        pressureDelta = currentADC - baselineADC;
        if (pressureDelta > PRESSURE_THRESHOLD) {
          lastAirflowTime = millis();
          break;  // Exit error state
        }
      }
    }
  }

  delay(LOOP_DELAY_MS);
}
