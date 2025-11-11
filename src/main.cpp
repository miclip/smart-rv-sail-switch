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
 * - PB3 (Arduino 3): Blower sense input - detects when blower motor is running
 * - PB4 (Arduino 4): Relay control output - HIGH to close (bypass sail)
 * - PB5 (Arduino 5): Sail sense input - monitors original sail switch state
 *
 * Wokwi Simulation Notes:
 * - Remove "frequency" attribute from diagram.json (breaks delay())
 * - Use analogRead(1) for PB2, NOT analogRead(2)
 * - Both switches need pull-down resistors
 *
 * License: CC BY-NC-SA 4.0 - See LICENSE file
 * Repository: https://github.com/miclip/smart-rv-sail-switch
 */
#include <Arduino.h>

// Pin definitions
const int BLOWER_PIN = 3;       // PB3 - Input: HIGH when blower running
const int SAIL_SENSE_PIN = 5;   // PB5 - Input: HIGH when original sail closed
const int IDLE_LED = 1;         // PB1 - Output: Red LED for idle/error
const int ACTIVE_LED = 0;       // PB0 - Output: Green LED when bypassing
const int SENSOR_PIN = 1;       // analogRead(1) for PB2 sensor (Wokwi)

// Tunable parameters
const int PRESSURE_THRESHOLD = 30;  // ADC counts above baseline
const int MAX_WAIT_SECONDS = 30;
const int DEBOUNCE_CHECKS = 3;

// Global variables
uint16_t baselineADC = 0;

void setup() {
  // Configure pins
  pinMode(BLOWER_PIN, INPUT);
  pinMode(SAIL_SENSE_PIN, INPUT);
  pinMode(IDLE_LED, OUTPUT);
  pinMode(ACTIVE_LED, OUTPUT);

  // Initialize to safe state
  digitalWrite(IDLE_LED, HIGH);   // Red LED on (idle)
  digitalWrite(ACTIVE_LED, LOW);  // Green LED off

  delay(500);

  // Calibrate baseline pressure (blower NOT running yet)
  uint32_t sum = 0;
  for (int i = 0; i < 8; i++) {
    sum += analogRead(SENSOR_PIN);
    delay(10);
  }
  baselineADC = sum / 8;

  // Sanity check
  if (baselineADC < 50 || baselineADC > 900) {
    // Error mode - rapid blink
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
}

void loop() {
  // Idle when blower is off
  if (digitalRead(BLOWER_PIN) == LOW) {
    digitalWrite(IDLE_LED, HIGH);
    digitalWrite(ACTIVE_LED, LOW);
    delay(100);
    return;
  }

  // Blower is running - turn off idle LED
  digitalWrite(IDLE_LED, LOW);

  // Wait for airflow to develop
  bool airflowDetected = false;
  int consecutiveDetections = 0;
  int waitCount = 0;

  while (waitCount < MAX_WAIT_SECONDS * 10) {
    uint16_t currentADC = analogRead(SENSOR_PIN);
    int16_t pressureDelta = currentADC - baselineADC;

    if (pressureDelta > PRESSURE_THRESHOLD) {
      consecutiveDetections++;
      if (consecutiveDetections >= DEBOUNCE_CHECKS) {
        airflowDetected = true;
        break;
      }
    } else {
      consecutiveDetections = 0;
    }

    delay(100);
    waitCount++;
  }

  // Hold state while blower runs, continuously check sail switch
  while (digitalRead(BLOWER_PIN) == HIGH) {
    // Hybrid mode: only bypass if airflow detected AND sail failed
    if (airflowDetected && digitalRead(SAIL_SENSE_PIN) == LOW) {
      digitalWrite(ACTIVE_LED, HIGH);  // Turn on green LED (bypass mode)
    } else {
      digitalWrite(ACTIVE_LED, LOW);   // Turn off green LED (sail working or no airflow)
    }
    delay(100);
  }

  // Blower stopped - reset to idle
  digitalWrite(ACTIVE_LED, LOW);
  digitalWrite(IDLE_LED, HIGH);
  delay(500);
}
