# ATtiny85 Pin Mapping Reference

## Physical DIP-8 Package to Arduino/AVR/ADC
```
Physical | AVR  | Arduino | ADC    | Notes
Pin      | Port | Pin     | Chan   |
---------|------|---------|--------|------------------
1        | PB5  | 5       | A0/ADC0| RESET (use as GPIO)
2        | PB3  | 3       | A3/ADC3|
3        | PB4  | 4       | A2/ADC2|
4        | GND  | GND     | -      |
5        | PB0  | 0       | -      | (no ADC)
6        | PB1  | 1       | -      | (no ADC)
7        | PB2  | 2       | A1/ADC1|
8        | VCC  | VCC     | -      |
```

## analogRead() Mapping
- `analogRead(A0)` or `analogRead(0)` -> reads PB5 (pin 1)
- `analogRead(A1)` or `analogRead(1)` -> reads PB2 (pin 7) <- SENSOR PIN
- `analogRead(A2)` or `analogRead(2)` -> reads PB4 (pin 3)
- `analogRead(A3)` or `analogRead(3)` -> reads PB3 (pin 2)

## digitalRead/Write() Mapping
- `digitalWrite(0, ...)` -> controls PB0 (pin 5)
- `digitalWrite(1, ...)` -> controls PB1 (pin 6)
- `digitalWrite(2, ...)` -> controls PB2 (pin 7)
- `digitalWrite(3, ...)` -> controls PB3 (pin 2)
- `digitalWrite(4, ...)` -> controls PB4 (pin 3)
- `digitalWrite(5, ...)` -> controls PB5 (pin 1)

## Our Circuit Connections (SDP810 I2C Version)
- PB0 (Arduino 0, pin 5) -> SDP810 SDA (I2C data) + 4.7K pull-up to 5V
- PB1 (Arduino 1, pin 6) -> Status LED
- PB2 (Arduino 2, pin 7) -> SDP810 SCL (I2C clock) + 4.7K pull-up to 5V
- PB3 (Arduino 3, pin 2) -> Sail Switch sense (with 10K pull-down)
- PB4 (Arduino 4, pin 3) -> Relay Output
- PB5 (Arduino 5, pin 1) -> RESET (ISP programming only)

## I2C Notes
- SDP810 address: 0x25
- Bit-banged I2C (no hardware I2C on ATtiny85)
- 4.7K pull-ups required on both SDA and SCL
