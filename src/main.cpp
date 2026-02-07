/*
 * Smart RV Sail Switch - ATtiny85 Firmware (SDP810 Version)
 * SIMPLIFIED TEST VERSION
 */
#include <Arduino.h>

// Pin definitions
#define SDA_PIN PB0
#define SCL_PIN PB2
#define LED_PIN PB1
#define RELAY_PIN PB4

// SDP810 I2C address
#define SDP810_ADDR 0x25

// Threshold - turn on above 5 Pa, turn off below 1 Pa
// Higher ON threshold confirms real airflow, lower OFF threshold keeps relay engaged
const int16_t THRESHOLD_ON = 5;
const int16_t THRESHOLD_OFF = 1;

// Global
int16_t baselinePa = 0;

// ============ I2C Bit-Bang ============

inline void i2c_delay() { delayMicroseconds(1); }

void i2c_init() {
  PORTB &= ~((1 << SDA_PIN) | (1 << SCL_PIN));
  DDRB &= ~((1 << SDA_PIN) | (1 << SCL_PIN));
}

void i2c_start() {
  DDRB &= ~(1 << SDA_PIN);
  DDRB &= ~(1 << SCL_PIN);
  i2c_delay();
  DDRB |= (1 << SDA_PIN);
  i2c_delay();
  DDRB |= (1 << SCL_PIN);
  i2c_delay();
}

void i2c_stop() {
  DDRB |= (1 << SDA_PIN);
  i2c_delay();
  DDRB &= ~(1 << SCL_PIN);
  i2c_delay();
  DDRB &= ~(1 << SDA_PIN);
  i2c_delay();
}

uint8_t i2c_write(uint8_t data) {
  for (uint8_t i = 0; i < 8; i++) {
    if (data & 0x80) {
      DDRB &= ~(1 << SDA_PIN);
    } else {
      DDRB |= (1 << SDA_PIN);
    }
    data <<= 1;
    i2c_delay();
    DDRB &= ~(1 << SCL_PIN);
    i2c_delay();
    DDRB |= (1 << SCL_PIN);
  }
  DDRB &= ~(1 << SDA_PIN);
  i2c_delay();
  DDRB &= ~(1 << SCL_PIN);
  i2c_delay();
  uint8_t ack = (PINB & (1 << SDA_PIN)) ? 1 : 0;
  DDRB |= (1 << SCL_PIN);
  return ack;
}

uint8_t i2c_read(uint8_t send_ack) {
  uint8_t data = 0;
  DDRB &= ~(1 << SDA_PIN);
  for (uint8_t i = 0; i < 8; i++) {
    data <<= 1;
    DDRB &= ~(1 << SCL_PIN);
    i2c_delay();
    if (PINB & (1 << SDA_PIN)) data |= 1;
    DDRB |= (1 << SCL_PIN);
    i2c_delay();
  }
  if (send_ack) {
    DDRB |= (1 << SDA_PIN);
  } else {
    DDRB &= ~(1 << SDA_PIN);
  }
  i2c_delay();
  DDRB &= ~(1 << SCL_PIN);
  i2c_delay();
  DDRB |= (1 << SCL_PIN);
  DDRB &= ~(1 << SDA_PIN);
  return data;
}

// ============ SDP810 ============

bool sdp810_start() {
  i2c_start();
  if (i2c_write((SDP810_ADDR << 1) | 0) != 0) { i2c_stop(); return false; }
  if (i2c_write(0x36) != 0) { i2c_stop(); return false; }
  if (i2c_write(0x03) != 0) { i2c_stop(); return false; }
  i2c_stop();
  delay(50);
  return true;
}

bool sdp810_read(int16_t *pa) {
  i2c_start();
  if (i2c_write((SDP810_ADDR << 1) | 1) != 0) { i2c_stop(); return false; }
  uint8_t msb = i2c_read(1);
  uint8_t lsb = i2c_read(0);
  i2c_stop();
  int16_t raw = (msb << 8) | lsb;
  *pa = raw / 60;
  return true;
}

// ============ Main ============

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_PIN, HIGH);

  i2c_init();
  delay(100);

  // Init sensor
  if (!sdp810_start()) {
    // Error: 2 blinks forever
    while (true) {
      digitalWrite(LED_PIN, HIGH); delay(100);
      digitalWrite(LED_PIN, LOW); delay(100);
      digitalWrite(LED_PIN, HIGH); delay(100);
      digitalWrite(LED_PIN, LOW); delay(500);
    }
  }

  // Wait for sensor to stabilize (warmup)
  delay(1000);

  // Read baseline - average 10 readings
  int32_t sum = 0;
  for (int i = 0; i < 10; i++) {
    int16_t pressure;
    if (!sdp810_read(&pressure)) {
      // Error: 3 blinks forever
      while (true) {
        digitalWrite(LED_PIN, HIGH); delay(100);
        digitalWrite(LED_PIN, LOW); delay(100);
        digitalWrite(LED_PIN, HIGH); delay(100);
        digitalWrite(LED_PIN, LOW); delay(100);
        digitalWrite(LED_PIN, HIGH); delay(100);
        digitalWrite(LED_PIN, LOW); delay(500);
      }
    }
    sum += pressure;
    delay(50);
  }
  baselinePa = sum / 10;

  // Success: 3 blinks then off
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH); delay(100);
    digitalWrite(LED_PIN, LOW); delay(100);
  }
}

void loop() {
  int16_t currentPa;
  if (!sdp810_read(&currentPa)) {
    // Read error - rapid blink, but DON'T change relay state
    digitalWrite(LED_PIN, HIGH); delay(30);
    digitalWrite(LED_PIN, LOW); delay(30);
    return;
  }

  int16_t delta = currentPa - baselinePa;

  // Hysteresis control with time-based debounce for turn-off
  static bool relayOn = false;
  static unsigned long lowStartTime = 0;
  const unsigned long OFF_DELAY_MS = 60000;  // 60 seconds (1 min) to turn off

  if (!relayOn && delta >= THRESHOLD_ON) {
    // Turn ON immediately when airflow detected
    relayOn = true;
    lowStartTime = 0;
    digitalWrite(RELAY_PIN, HIGH);
  } else if (relayOn) {
    if (delta < THRESHOLD_OFF) {
      // Pressure is low - start or continue timing
      if (lowStartTime == 0) {
        lowStartTime = millis();
      } else if (millis() - lowStartTime >= OFF_DELAY_MS) {
        // Been low for 5 seconds - turn off
        relayOn = false;
        digitalWrite(RELAY_PIN, LOW);
        lowStartTime = 0;
      }
    } else {
      // Pressure is good - reset timer
      lowStartTime = 0;
    }
  }

  // LED shows state: ON = airflow detected, OFF = idle
  digitalWrite(LED_PIN, relayOn ? HIGH : LOW);

  delay(100);
}
