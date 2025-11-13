/*
 * Blower Simulator - Test Controller
 *
 * Controls a 120mm PWM fan via potentiometer to simulate RV furnace
 * blower at different speeds for testing the Smart Sail Switch.
 *
 * Pin Configuration:
 * - PB0 (Arduino 0): PWM output to fan (in Wokwi: servo for visualization)
 * - PB1 (ADC1): Potentiometer input (speed dial)
 * - PB2 (Arduino 2): Power LED (always on when running)
 * - PB3 (Arduino 3): Sail circuit monitor (from Smart Sail Switch)
 * - PB4 (Arduino 4): Ignition LED (lit when sail circuit closed)
 *
 * Usage:
 * 1. Connect 12V PWM fan to PB0 via MOSFET driver
 * 2. Connect 10kΩ potentiometer to PB1
 * 3. Connect Smart Sail Switch sail circuit output to PB3
 * 4. Turn dial to control fan speed
 * 5. Observe when Smart Sail Switch detects airflow (its green LED)
 * 6. Observe when sail circuit closes (ignition LED on PB4)
 *
 * License: CC BY-NC-SA 4.0 - See LICENSE file
 * Repository: https://github.com/miclip/smart-rv-sail-switch
 */
#include <Arduino.h>

// Pin definitions
const int FAN_PWM_PIN = 0;        // PB0 - PWM output to fan
const int POWER_LED = 1;          // PB1 - Power indicator LED
const int DIAL_PIN = 1;           // PB2 - Potentiometer input (analogRead(1) for PB2)
const int SAIL_CIRCUIT_PIN = 3;   // PB3 - Monitor sail circuit from device
const int IGNITION_LED = 4;       // PB4 - Lit when sail circuit closed

void setup() {
  // Configure pins
  pinMode(FAN_PWM_PIN, OUTPUT);
  pinMode(POWER_LED, OUTPUT);
  pinMode(IGNITION_LED, OUTPUT);
  pinMode(SAIL_CIRCUIT_PIN, INPUT);

  // Start with fan off
  analogWrite(FAN_PWM_PIN, 0);

  // Power LED on
  digitalWrite(POWER_LED, HIGH);
  digitalWrite(IGNITION_LED, LOW);

  // Startup blink sequence
  for (int i = 0; i < 3; i++) {
    digitalWrite(POWER_LED, LOW);
    delay(100);
    digitalWrite(POWER_LED, HIGH);
    delay(100);
  }

  // Test PWM sweep to verify it works (0-255)
  for (int pwm = 0; pwm <= 255; pwm += 64) {
    analogWrite(FAN_PWM_PIN, pwm);
    delay(300);
  }
  analogWrite(FAN_PWM_PIN, 0);
  delay(300);
}

void loop() {
  // Read dial position (0-1023)
  int dialValue = analogRead(DIAL_PIN);

  // Map to PWM value (0-255)
  // 0% = 0 (fan off)
  // 100% = 255 (full speed)
  int pwmValue = map(dialValue, 0, 1023, 0, 255);

  // Set PWM output (controls fan speed / servo position in Wokwi)
  analogWrite(FAN_PWM_PIN, pwmValue);

  // Also blink power LED to show pot is being read
  // (helps debug if servo doesn't move)
  int blinkDelay = map(dialValue, 0, 1023, 1000, 100);
  static unsigned long lastBlink = 0;
  static bool ledState = false;
  if (millis() - lastBlink > blinkDelay) {
    ledState = !ledState;
    digitalWrite(POWER_LED, ledState);
    lastBlink = millis();
  }

  // Monitor sail circuit from Smart Sail Switch
  // HIGH = circuit closed (either sail closed or relay bypassed)
  if (digitalRead(SAIL_CIRCUIT_PIN) == HIGH) {
    digitalWrite(IGNITION_LED, HIGH);  // Furnace would ignite
  } else {
    digitalWrite(IGNITION_LED, LOW);   // Furnace would not ignite
  }

  // Update every 50ms (fast enough for smooth control)
  delay(50);
}
