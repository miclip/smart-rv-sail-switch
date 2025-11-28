/*
 * SDP810 Data Check
 * Shows what raw data we're getting:
 * - All 0x00: LED solid ON
 * - All 0xFF: very fast blink
 * - Other: blink count = high nibble of MSB
 */

#include <Arduino.h>

#define LED PB1
#define SDA PB0
#define SCL PB2
#define SDP810_ADDR 0x25

inline void i2c_delay() { delayMicroseconds(1); }

void i2c_start() {
  DDRB &= ~(1 << SDA); DDRB &= ~(1 << SCL); i2c_delay();
  DDRB |= (1 << SDA); i2c_delay();
  DDRB |= (1 << SCL); i2c_delay();
}

void i2c_stop() {
  DDRB |= (1 << SDA); i2c_delay();
  DDRB &= ~(1 << SCL); i2c_delay();
  DDRB &= ~(1 << SDA); i2c_delay();
}

uint8_t i2c_write(uint8_t data) {
  for (uint8_t i = 0; i < 8; i++) {
    if (data & 0x80) DDRB &= ~(1 << SDA);
    else DDRB |= (1 << SDA);
    data <<= 1; i2c_delay();
    DDRB &= ~(1 << SCL); i2c_delay();
    DDRB |= (1 << SCL);
  }
  DDRB &= ~(1 << SDA); i2c_delay();
  DDRB &= ~(1 << SCL); i2c_delay();
  uint8_t ack = (PINB & (1 << SDA)) ? 1 : 0;
  DDRB |= (1 << SCL);
  return ack;
}

uint8_t i2c_read(uint8_t send_ack) {
  uint8_t data = 0;
  DDRB &= ~(1 << SDA);
  for (uint8_t i = 0; i < 8; i++) {
    data <<= 1;
    DDRB &= ~(1 << SCL); i2c_delay();
    if (PINB & (1 << SDA)) data |= 1;
    DDRB |= (1 << SCL); i2c_delay();
  }
  if (send_ack) DDRB |= (1 << SDA);
  else DDRB &= ~(1 << SDA);
  i2c_delay();
  DDRB &= ~(1 << SCL); i2c_delay();
  DDRB |= (1 << SCL);
  DDRB &= ~(1 << SDA);
  return data;
}

void setup() {
  DDRB |= (1 << LED);
  PORTB &= ~((1 << SDA) | (1 << SCL));
  DDRB &= ~((1 << SDA) | (1 << SCL));
  delay(100);

  // Start continuous: 0x3603
  i2c_start();
  i2c_write((SDP810_ADDR << 1) | 0);
  i2c_write(0x36);
  i2c_write(0x03);
  i2c_stop();
  delay(10);
}

void loop() {
  i2c_start();
  i2c_write((SDP810_ADDR << 1) | 1);
  uint8_t msb = i2c_read(1);
  uint8_t lsb = i2c_read(0);
  i2c_stop();

  if (msb == 0x00 && lsb == 0x00) {
    // All zeros - solid ON
    PORTB |= (1 << LED);
    delay(1000);
  } else if (msb == 0xFF && lsb == 0xFF) {
    // All ones - very fast blink
    for (int i = 0; i < 20; i++) {
      PORTB ^= (1 << LED);
      delay(25);
    }
  } else {
    // Got some data - blink MSB high nibble + 1 times
    uint8_t count = (msb >> 4) + 1;
    for (int i = 0; i < count; i++) {
      PORTB |= (1 << LED);
      delay(150);
      PORTB &= ~(1 << LED);
      delay(150);
    }
    delay(1000);
  }
}
