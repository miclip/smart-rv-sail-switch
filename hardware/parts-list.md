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
| SDP810-500Pa | SDP810-500Pa | 1 | Differential, ±500 Pa, I2C | Sensirion digital sensor, 4-pin, I2C address 0x25 |

### I2C Pull-up Resistors
| Item | Part Number | Quantity | Specs | Notes |
|------|-------------|----------|-------|-------|
| 4.7K ohm resistor | - | 2 | 1/4W through-hole | Pull-ups for SDA and SCL to 5V |

### Voltage Regulation
| Item | Part Number | Quantity | Specs | Notes |
|------|-------------|----------|-------|-------|
| 5V Regulator | L7805CV-DG (TO-220) | 1 | 5V output, 1A+ | JLCPCB part C3795 |
| Heatsink | TO-220 compatible | 1 | - | Optional but recommended |

### Relay Module
| Item | Part Number | Quantity | Specs | Notes |
|------|-------------|----------|-------|-------|
| 5V Relay Module | KY-019 or equivalent | 1 | Single channel, opto-isolated, active-high, 10A contacts | Coil: 5V DC, Contacts: 10A at 12V DC minimum |

### Resistors (SMD - Assembled by JLCPCB)
| Value | Quantity | Package | LCSC Part | Purpose |
|-------|----------|---------|-----------|---------|
| 10K ohm | 3 | 0805 SMD | C3016734 | R1: Sail switch pull-down, R2/R3: LED current limiting |

### Capacitors
| Value | Quantity | Type | Voltage | LCSC Part | Purpose |
|-------|----------|------|---------|-----------|---------|
| 100nF | 2 | Ceramic 0805 SMD | C2830721 | C1/C2: Regulator input/output filtering (assembled by JLCPCB) |
| 100µF | 1 | Electrolytic through-hole | C2960378 | C3: Output stability (hand-solder) |

## Optional Protection Components

| Item | Part Number | Quantity | Specs | Purpose |
|------|-------------|----------|-------|---------|
| Zener diode | 1N4733A | 1 | 5.1V, 1W | Overvoltage protection |
| Toggle switch | SPST | 1 | 10A 12V rating | Manual emergency bypass |
| Fuse holder + fuse | Inline | 1 | 3A-5A | Overcurrent protection |

## LEDs (Status Indicators - Through-Hole, Hand-Solder)

| Type | Quantity | Color | LCSC Part | Purpose |
|------|----------|-------|-----------|---------|
| 3mm LED | 1 | Red | C84774 (EVERLIGHT 204-10SDRD/S530-A3-L) | Idle indicator (PB1) |
| 3mm LED | 1 | Green | C183839 (EVERLIGHT 204-10SUGD/S400-A4) | Active/Bypass indicator (PB0) |

## Wiring & Connectors

| Item | Quantity | Specs | LCSC Part | Purpose |
|------|----------|-------|-----------|---------|
| 2x3 ISP Header | 1 | 2.54mm pitch, male | C42431837 | Programming header (on PCB) |
| 1x3 Female Socket | 2 | 2.54mm pitch | C18078126 | U1: Pressure sensor, U6: Relay module |
| 2-pin Screw Terminal | 2 | 5.0mm pitch | C474881 | U4: 12V input, U5: Sail switch |
| Silicone tubing | 2-3 feet | 1/8" ID (3mm), high-temp rated | - | Sensor to blower duct |
| Automotive wire | 10-15 feet | 18 AWG, multiple colors | - | Furnace connections |
| Crimp connectors | 10-15 | Insulated spade or butt connectors | - | Furnace wiring |
| Heat shrink tubing | Assortment | Various sizes | - | Insulation |
| Zip ties | 10-20 | Small, UV resistant | - | Cable management |

## PCB Manufacturing

| Item | Quantity | Specs | Purpose |
|------|----------|-------|---------|
| Custom PCB | 1 | EasyEDA Pro design | Schematic in /home/miclip/Downloads/Schematic.pdf |
| PCB Assembly | - | JLCPCB SMD assembly | R1, R2, R3, C1, C2 pre-soldered |
| Through-hole parts | - | Hand-solder | ATtiny85, L7805, LEDs, headers, terminals, C3 |

## Optional: Breadboard Testing

| Item | Quantity | Specs | Purpose |
|------|----------|-------|---------|
| Solderless breadboard | 1 | 400 or 830 point | Testing circuit before PCB |
| Jumper wire kit | 1 | Male-male/female | Breadboard connections |
| DIP-8 IC socket | 1 | 2.54mm pitch | For ATtiny85 (makes it removable) |

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
- **SDP810 wiring**: Sensor has 4 pins - use short wires and ensure solid I2C pull-ups

## Next Steps

Once you have your parts:
1. Organize components in labeled containers
2. Test voltage regulator output with multimeter
3. Proceed to [03-building.md](../docs/03-building.md)
