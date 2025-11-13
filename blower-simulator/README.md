# Blower Simulator

Test rig for validating the Smart Sail Switch under controlled airflow conditions.

## Purpose

This is a bench test platform that simulates an RV furnace blower to test the Smart Sail Switch before installation. It allows you to:

- Control airflow speed with a potentiometer (dial)
- Test sensor response at different airflow levels
- Verify sail switch detection logic
- Find threshold values for pressure detection
- Validate hybrid mode behavior

## Hardware Components

- ATtiny85 microcontroller (test controller)
- 120mm PWM fan (blower motor simulator)
- 10kΩ potentiometer (speed control dial)
- 12V power supply
- LEDs for status indication
- Optional: Real sail switch for complete testing

See [hardware/README.md](hardware/README.md) for schematics and [parts-list.md](parts-list.md) for complete BOM.

## How It Works

The test controller reads a potentiometer and outputs a PWM signal to control the fan speed. This simulates different airflow conditions:

- **High speed (100%)** - Normal low-altitude operation
- **Medium speed (50%)** - Mid-altitude conditions
- **Low speed (20-30%)** - High-altitude weak airflow (sail may fail)

The Smart Sail Switch (device under test) connects to this rig and responds to the simulated airflow.

## Setup

### 1. Build Hardware
Follow the wiring diagram in [hardware/wiring.md](hardware/wiring.md)

### 2. Program Controller
```bash
cd blower-simulator
./scripts/build.sh
./scripts/upload.sh
```

### 3. Connect Device Under Test
Wire your Smart Sail Switch to the blower simulator according to the test setup diagram.

### 4. Power On and Test
1. Turn dial to minimum
2. Power on both devices
3. Slowly increase dial
4. Observe when Smart Sail Switch detects airflow
5. Note threshold values

## Testing Procedure

See [docs/testing-procedure.md](docs/testing-procedure.md) for complete test protocols.

## Simulation

Wokwi simulation available for testing the controller logic before building hardware:

```bash
cd blower-simulator
pio run -e wokwi
wokwi-cli .
```

## Development

- Firmware: [src/main.cpp](src/main.cpp)
- PlatformIO config: [platformio.ini](platformio.ini)
- Wokwi circuit: [diagram.json](diagram.json)
