# Getting Started

**New to Arduino and ATtiny? This guide will walk you through everything you need to know.**

## What You're Building

The Smart RV Sail Switch is a small circuit board (about the size of a matchbox) that:
- Monitors your RV furnace blower airflow using a pressure sensor
- Detects when the original sail switch fails at high altitude
- Safely provides a backup signal to let the furnace operate
- Shuts down automatically when the heat cycle ends

## Prerequisites

### Knowledge Requirements

You should be comfortable with:
- **Basic electronics** - understanding voltage, ground, and circuits
- **Soldering** - or willing to learn (plenty of online tutorials available)
- **Using a multimeter** - measuring voltage and continuity
- **Following wiring diagrams**
- **Basic computer skills** - installing software, using USB devices

**No programming experience needed** - the code is provided and ready to upload.

### Time Estimate

- **First-time builders**: 6-10 hours (learning, assembly, testing)
- **Experienced makers**: 2-4 hours
- **Installation in RV**: 2-3 hours

Plan to spread this over several days - don't rush safety-critical work.

## What You'll Need

### Hardware Components (~$30-40)

See [hardware/parts-list.md](../hardware/parts-list.md) for complete list with links. Key items:

- ATtiny85 microcontroller chip ($2-3)
- SDP810-500Pa pressure sensor ($15-25) - I2C digital sensor
- USBtinyISP programmer ($8-15) - to upload code to ATtiny
- 5V relay module ($2-5)
- Voltage regulator and basic components ($5-10)
- Breadboard for testing ($5)

### Tools Required

**Must Have:**
- Soldering iron (25-40W) and solder
- Multimeter (digital, ~$15-30)
- Wire strippers/cutters
- Small screwdrivers
- Computer with USB port (Windows, Mac, or Linux)

**Nice to Have:**
- Helping hands/PCB holder
- Heat shrink tubing and heat gun
- Label maker for wires
- Breadboard jumper wire kit

### Software (Free)

- **Arduino IDE** - software to program the ATtiny85
- **ATtiny board support** - add-on for Arduino IDE
- **USB drivers** - for your programmer (usually automatic)

We'll install these in the next guide.

## Project Phases

### Phase 1: Learn & Prepare (1-2 hours)
1. Read all safety information ([SAFETY.md](../SAFETY.md))
2. Read this entire guide series
3. Order components from parts list
4. Gather tools

### Phase 2: Software Setup (30 min - 1 hour)
1. Install Arduino IDE
2. Configure for ATtiny85
3. Test programmer connection

See [02-arduino-setup.md](02-arduino-setup.md)

### Phase 3: Breadboard Testing (2-3 hours)
1. Assemble circuit on breadboard
2. Upload test code
3. Verify sensor readings
4. Test relay operation

See [03-building.md](03-building.md)

### Phase 4: Program ATtiny (1 hour)
1. Upload final firmware
2. Test all functions
3. Verify LED indicators

See [04-programming.md](04-programming.md)

### Phase 5: Permanent Assembly (2-3 hours)
1. Solder circuit on perfboard
2. Install in enclosure
3. Prepare wiring harness
4. Final testing

See [03-building.md](03-building.md)

### Phase 6: Bench Testing (1-2 hours)
1. Simulate furnace operation
2. Test all modes (normal, bypass, error)
3. Verify fail-safes

See [05-testing.md](05-testing.md)

### Phase 7: RV Installation (2-3 hours)
1. Identify furnace wiring
2. Install sensor and circuit
3. Test at low altitude first
4. Monitor operation

See [06-installation.md](06-installation.md)

## Understanding the ATtiny85

### What is it?

The ATtiny85 is a tiny microcontroller (the "brain" of your project):
- About the size of a large bean
- 8 pins total (6 usable for your circuit)
- Programmed using Arduino language
- Runs on 5V
- Very low power consumption

### Why ATtiny85 instead of Arduino?

- **Much smaller** - fits in compact enclosure
- **Cheaper** - $2 vs $20+ for Arduino
- **Lower power** - important for RV battery life
- **Perfect for simple tasks** - has everything we need

### ATtiny85 Limitations

- No built-in USB (need external programmer)
- Limited pins (8 total)
- Less memory than Arduino
- No hardware serial for debugging (we use LEDs instead)

For this project, these limitations don't matter.

## Understanding the SDP810-500Pa Sensor

### What does it do?

Measures the **difference** in air pressure between two ports:
- **One port**: Connected via tube to blower duct (higher pressure when blower runs)
- **Other port**: Open to room air (ambient pressure)
- **Output**: Digital I2C data (±500 Pa range, ~15 Pa typical from RV blower)

### Why this sensor?

- **High sensitivity** - detects low pressure differentials from RV blowers
- **Digital I2C output** - more accurate and noise-resistant than analog
- **Temperature compensated** - works in cold RV winters
- **Wide voltage range** - runs on 2.7-5.5V
- **Reliable** - Sensirion quality

## Common Questions

**Q: Do I need programming experience?**
A: No. The code is provided. You just upload it using Arduino IDE (like copying a file).

**Q: What if I've never soldered?**
A: Plenty of beginner tutorials on YouTube. Practice on scrap wire first. This project uses through-hole components (easier than surface mount).

**Q: Can I use a different microcontroller?**
A: Yes! The code could be adapted for Arduino Nano, ESP8266, etc. ATtiny85 is just compact and cheap.

**Q: What if something doesn't work?**
A: See [07-troubleshooting.md](07-troubleshooting.md). The design includes LED indicators to help diagnose issues.

**Q: Is this safe?**
A: With proper installation, testing, and monitoring - yes. But READ [SAFETY.md](../SAFETY.md) completely. This modifies a safety device.

**Q: Will this void my warranty?**
A: Probably yes for the furnace. Check your RV manufacturer's policy.

**Q: Can I pay someone to build this?**
A: You could hire a local maker/electronics hobbyist for assembly, but installation should involve an RV technician familiar with furnaces.

## Next Steps

Ready to proceed? Continue to:

**[02-arduino-setup.md](02-arduino-setup.md)** - Setting up Arduino IDE and your programmer

---

**Not ready yet?** That's okay! Bookmark this page and come back when you have:
- Read all safety information
- Ordered your components
- Set aside time to work through the guides

Questions? Open an issue on GitHub or consult the troubleshooting guide.
