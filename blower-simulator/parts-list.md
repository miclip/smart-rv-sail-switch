# Blower Simulator Parts List

## Required Components

### Electronics

| Item | Qty | Specs | Est. Cost | Notes |
|------|-----|-------|-----------|-------|
| ATtiny85 DIP-8 | 1 | 8MHz internal | $2 | Test controller |
| 120mm PWM Fan | 1 | 12V, 4-pin, high CFM | $15-25 | Wathai 12038 or similar |
| N-channel MOSFET | 1 | IRLZ44N or similar | $1 | For PWM fan control |
| 10kΩ Potentiometer | 1 | Linear taper | $2 | Speed control dial |
| LEDs | 2 | 5mm, any color | $0.50 | Power + Ignition indicators |
| 220Ω Resistors | 2 | 1/4W | $0.20 | LED current limiting |
| 10kΩ Resistor | 1 | 1/4W | $0.10 | MOSFET gate pull-down |
| 12V Power Supply | 1 | 2A minimum | $10 | For fan power |
| 5V Regulator | 1 | 7805 or LM7805 | $1 | Power ATtiny85 from 12V |
| Breadboard | 1 | Full size or half | $5 | Prototyping |
| Jumper Wires | 1 set | M/M | $5 | Connections |

### Optional (Complete Testing)

| Item | Qty | Specs | Est. Cost | Notes |
|------|-----|-------|-----------|-------|
| Real Sail Switch | 1 | RV furnace sail switch | $15-30 | For authentic testing |
| Tubing/Ducting | 1m | 4-5" diameter | $5 | Direct airflow |
| Project Enclosure | 1 | As needed | $10 | Mount components |

**Total Estimated Cost: $35-45** (without optional components)

## Where to Buy

- **ATtiny85, resistors, LEDs**: DigiKey, Mouser, Amazon
- **PWM Fan**: Amazon, Newegg (search "120mm PWM high CFM")
- **MOSFET**: DigiKey, Mouser (IRLZ44N recommended)
- **Power supply**: Amazon, electronics stores
- **Sail switch**: RV parts suppliers, eBay (search "RV furnace sail switch")

## Recommended Fan

**Wathai 12038 120mm PWM Fan**
- 120x120x38mm
- 5300 RPM max
- 230 CFM
- 12V 4-pin PWM
- Available on Amazon

This fan provides enough airflow to properly test the pressure sensor and sail switch under various conditions.

## Tools Needed

- Soldering iron
- Wire cutters/strippers
- Multimeter
- USBtinyISP programmer (for ATtiny85)
- Small screwdriver set
