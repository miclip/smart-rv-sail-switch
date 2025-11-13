# Blower Simulator Hardware

## Circuit Overview

The blower simulator uses an ATtiny85 to read a potentiometer and generate a PWM signal to control fan speed.

## Pin Connections

### ATtiny85 Pinout (DIP-8)
```
     ATtiny85
   +-----------+
   |  1  U  8  |  1: PB5 (RESET)  8: VCC (5V)
   |  2     7  |  2: PB3 (sail)   7: PB2 (power LED)
   |  3     6  |  3: PB4 (ign)    6: PB1 (pot)
   |  4     5  |  4: GND          5: PB0 (PWM out)
   +-----------+
```

### Connections

**PB0 (Pin 5) - Fan PWM Output:**
- Connect to MOSFET gate (via 220Ω resistor)
- MOSFET source to GND
- MOSFET drain to fan negative
- Fan positive to 12V

**PB1 (Pin 6) - Speed Control Potentiometer:**
- Pot terminal 1: 5V
- Pot wiper: PB1
- Pot terminal 3: GND

**PB2 (Pin 7) - Power LED:**
- PB2 -> 220Ω resistor -> LED anode
- LED cathode -> GND

**PB3 (Pin 2) - Sail Circuit Input:**
- Connect to Smart Sail Switch relay output
- 10kΩ pull-down resistor to GND

**PB4 (Pin 3) - Ignition LED:**
- PB4 -> 220Ω resistor -> LED anode
- LED cathode -> GND

**VCC (Pin 8):**
- 5V from voltage regulator

**GND (Pin 4):**
- Common ground

## MOSFET Driver Circuit

Since the ATtiny85 outputs 5V and the fan runs on 12V, use a MOSFET:

```
PB0 (PWM) -> 220Ω resistor -> MOSFET Gate
                               |
12V+ -------------------------+
                               |
                           Fan Motor
                               |
                         MOSFET Drain
                               |
MOSFET Source -> GND          |
    |                         |
    +------- 10kΩ pull-down --+
```

**Recommended MOSFET:** IRLZ44N (logic-level, N-channel)

## Power Supply

- **12V rail**: For fan motor (2A minimum)
- **5V rail**: For ATtiny85 and LEDs
  - Use 7805 voltage regulator from 12V
  - Input: 12V from PSU
  - Output: 5V for ATtiny85
  - Add 0.1µF capacitors for stability

## 4-Pin PWM Fan Connections

Standard PC fan pinout:
1. **Black** - Ground
2. **Yellow** - 12V+
3. **Green** - Tachometer (RPM feedback, not used)
4. **Blue** - PWM control signal

Connect:
- Black -> MOSFET drain
- Yellow -> 12V+
- Green -> Leave disconnected (or optionally to ATtiny85 input for RPM monitoring)
- Blue -> PB0 via MOSFET

Note: Some fans use PWM on pin 4 directly (5V signal). Check your fan's datasheet.

## Wokwi Simulation Limitations

The Wokwi simulation doesn't include:
- PWM fan component
- MOSFET driver circuit
- 12V power rail

The simulation tests the **controller logic only**:
- Potentiometer reading
- PWM signal generation (observe on PB0 with logic analyzer)
- Sail circuit monitoring
- LED status indication

For full hardware testing, build the actual circuit on breadboard.

## Breadboard Layout

TODO: Add Fritzing diagram or photo

## PCB Design

For permanent installation, consider designing a PCB that includes:
- ATtiny85 socket
- MOSFET driver
- Voltage regulator (12V -> 5V)
- Terminal blocks for connections
- LED indicators
- Potentiometer mount

## Safety Notes

- Use appropriate wire gauge for fan current (20-22 AWG minimum)
- Add fuse on 12V rail (2A fast-blow)
- Ensure MOSFET has adequate cooling if running high currents
- Double-check polarity before powering on
