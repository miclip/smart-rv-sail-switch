# Parts List (Bill of Materials)

**Estimated cost: $30-50** (excluding tools you may already have)

## Core Components

### Microcontroller
| Item | Part Number | Quantity | Specs | Notes |
|------|-------------|----------|-------|-------|
| ATtiny85 | ATtiny85-20PU | 1 | DIP-8 package, 20MHz capable | Get 2-3 for spares |

### Pressure Sensor
| Item | Part Number | Quantity | Specs | Notes |
|------|-------------|----------|-------|-------|
| MPXV5004DP | MPXV5004DP or MPXV5004DP-ND | 1 | Differential/Gauge, 0-3.92 kPa | Temperature compensated, breakout board versions available |

### Voltage Regulation
| Item | Part Number | Quantity | Specs | Notes |
|------|-------------|----------|-------|-------|
| 5V Regulator | LM7805 (TO-220) or LM1117-5.0 (SOT-223) | 1 | 5V output, 1A+ | LM7805 easier for breadboard |
| Heatsink | TO-220 compatible | 1 | - | Optional but recommended for LM7805 |

### Relay Module
| Item | Part Number | Quantity | Specs | Notes |
|------|-------------|----------|-------|-------|
| 5V Relay Module | KY-019 or equivalent | 1 | Single channel, opto-isolated, active-high, 10A contacts | Coil: 5V DC, Contacts: 10A at 12V DC minimum |

### Resistors
| Value | Quantity | Power Rating | Purpose |
|-------|----------|--------------|---------|
| 10K ohm | 3 | 1/4W or 1/2W, 5% tolerance | Voltage dividers (2x in series = 20K, 1x = 10K) |
| 1K ohm | 1 | 1/4W or 1/2W | Relay driver (if not built into module) |
| 220-330 ohm | 3 | 1/4W or 1/2W | LED current limiting |

### Capacitors
| Value | Quantity | Type | Voltage | Purpose |
|-------|----------|------|---------|---------|
| 10uF | 2 | Electrolytic | 25V or higher | Regulator input/output filtering |
| 0.1uF | 2-3 | Ceramic | 50V | Decoupling (ATtiny and stability) |
| 100uF | 1 | Electrolytic | 25V or higher | Optional: extra input stability |

## Optional Protection Components

| Item | Part Number | Quantity | Specs | Purpose |
|------|-------------|----------|-------|---------|
| Zener diode | 1N4733A | 1 | 5.1V, 1W | Overvoltage protection |
| Toggle switch | SPST | 1 | 10A 12V rating | Manual emergency bypass |
| Fuse holder + fuse | Inline | 1 | 3A-5A | Overcurrent protection |

## LEDs (Status Indicators)

| Type | Quantity | Color | Purpose |
|------|----------|-------|---------|
| 5mm LED | 1 | Red | Idle/Error indicator |
| 5mm LED | 1 | Green | Active/Bypass indicator |
| 5mm LED | 1 | Yellow | Optional: Calibrating indicator |

## Wiring & Connectors

| Item | Quantity | Specs | Purpose |
|------|----------|-------|---------|
| Silicone tubing | 2-3 feet | 1/8" ID (3mm), high-temp rated | Sensor to blower duct |
| Automotive wire | 10-15 feet | 18 AWG, multiple colors | Furnace connections |
| Crimp connectors | 10-15 | Insulated spade or butt connectors | Furnace wiring |
| Vampire taps | 2-4 | Posi-Tap or equivalent | Tapping existing wires |
| Heat shrink tubing | Assortment | Various sizes | Insulation |
| Zip ties | 10-20 | Small, UV resistant | Cable management |

## Prototyping & Assembly

| Item | Quantity | Specs | Purpose |
|------|----------|-------|---------|
| Solderless breadboard | 1 | 400 or 830 point | Testing circuit |
| Jumper wire kit | 1 | Male-male/female | Breadboard connections |
| Perfboard/protoboard | 1 | 5x7cm or 7x9cm | Permanent assembly |
| DIP-8 IC socket | 1 | 2.54mm pitch | For ATtiny85 (makes it removable) |
| Pin headers | 1 strip | Male/female, 2.54mm pitch | Component connections |

## Enclosure

| Item | Quantity | Specs | Purpose |
|------|----------|-------|---------|
| Plastic project box | 1 | 4" x 3" x 2" approx, weatherproof (IP65 rated) | Protects circuit in RV |
| Cable glands | 2-3 | PG7 or PG9 | Weatherproof wire entry |
| Mounting screws | 4 | #6 or #8, vibration-resistant | Secure mounting |

## Programming Hardware

| Item | Quantity | Specs | Purpose |
|------|----------|-------|---------|
| USBtinyISP programmer | 1 | AVR ISP compatible | Upload code to ATtiny85 |
| USB cable | 1 | Type-A to Type-B | For programmer (usually included) |

**Note:** Arduino Uno/Nano can be used as ISP programmer as an alternative.

## Required Tools

| Tool | Specs | Purpose |
|------|-------|---------|
| Digital multimeter | - | Essential for testing voltages and continuity |
| Soldering iron | 25-40W, temperature controlled recommended | Permanent assembly |
| Solder | 60/40 rosin-core or lead-free | Soldering connections |
| Wire strippers | Automatic recommended | Stripping wire insulation |
| Flush cutters | - | Trimming component leads |
| Heat gun or lighter | - | Heat shrink tubing |

## Testing Equipment

| Item | Specs | Purpose |
|------|-------|---------|
| 12V DC power supply | 1A minimum | Bench testing (or use RV battery) |
| CO detector | - | **REQUIRED** for safety monitoring |

## Notes

- **Part substitutions**: Most components have alternatives - contact manufacturer datasheets for equivalent specifications
- **Quality matters**: Use genuine parts for pressure sensor and voltage regulator
- **Automotive-grade wire**: Required for furnace installation due to temperature and vibration
- **Breakout boards**: Recommended for MPXV5004DP - easier to wire than bare sensor

## Next Steps

Once you have your parts:
1. Organize components in labeled containers
2. Test voltage regulator output with multimeter
3. Proceed to [03-building.md](../docs/03-building.md)
