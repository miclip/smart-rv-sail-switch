# Development Quick Start

## For Developers

This project uses **PlatformIO** with **CLion IDE**.

### Quick Setup

```bash
# 1. Clone repository
git clone https://github.com/miclip/smart-rv-sail-switch.git
cd smart-rv-sail-switch

# 2. Install dependencies (if using CLI)
pio pkg install

# 3. Build
pio run -e attiny85

# 4. Upload to hardware
pio run -e attiny85 --target upload

# 5. Run simulation (requires Wokwi)
pio run -e wokwi
wokwi-cli .
```

### Project Structure

- `src/main.cpp` - Main firmware
- `platformio.ini` - Build configuration
- `diagram.json` - Wokwi simulation
- `examples/` - Test sketches

### Environments

**`attiny85`** - Real hardware with USBtinyISP
**`wokwi`** - Simulation in browser

### Wokwi Simulation

The project includes a Wokwi simulation for testing.

**Important Wokwi-specific settings:**

1. **diagram.json**: Remove `"frequency"` attribute from ATtiny85 - it breaks `delay()`
2. **ADC mapping**: Use `analogRead(1)` for PB2, not `analogRead(2)`
3. **Switches**: Both blower and sail switches need 10kΩ pull-down resistors

**To run simulation:**
```bash
# Build firmware
pio run -e wokwi

# Run in VS Code with Wokwi extension
# OR run with CLI:
wokwi-cli .
```

See `ATTINY85_PINS.md` for complete pin mapping reference.

### Full Documentation

See [docs/02-development-setup.md](docs/02-development-setup.md) for complete setup instructions.

## For End Users

If you just want to build the device, see [docs/01-getting-started.md](docs/01-getting-started.md) for beginner-friendly instructions using Arduino IDE.
