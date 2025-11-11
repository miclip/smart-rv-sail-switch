# Development Setup (CLion + PlatformIO + Wokwi)

This project uses a modern development workflow with CLion IDE, PlatformIO build system, and Wokwi simulator.

## Prerequisites

### Required Software

1. **CLion IDE** - JetBrains C/C++ IDE
   - Download from: https://www.jetbrains.com/clion/
   - Free for students/open source, 30-day trial otherwise

2. **PlatformIO Plugin** for CLion
   - Install from CLion: Settings -> Plugins -> Marketplace -> Search "PlatformIO"
   - Or install PlatformIO Core CLI: https://docs.platformio.org/en/latest/core/installation/index.html

3. **Wokwi** for simulation (optional but recommended)
   - VS Code extension OR CLI tool
   - Download: https://wokwi.com/
   - Wokwi CLI: `curl -L https://wokwi.com/ci/install.sh | sh`

4. **USBtinyISP Drivers** (for hardware upload)
   - Linux: Already included in kernel
   - macOS: Install via libusb
   - Windows: https://learn.adafruit.com/usbtinyisp/drivers

## Project Structure

```
smart-rv-sail-switch/
├── platformio.ini          # PlatformIO configuration
├── wokwi.toml             # Wokwi simulator config
├── diagram.json           # Wokwi circuit diagram
│
├── src/                   # Source code
│   └── main.cpp          # Main firmware (ATtiny85)
│
├── lib/                   # Project-specific libraries
│
├── test/                  # Unit tests
│
├── scripts/               # Build and deployment scripts
│
├── hardware/              # Circuit docs
├── docs/                  # Documentation
└── images/                # Diagrams and photos
```

## Setup Instructions

### 1. Clone Repository

```bash
git clone https://github.com/miclip/smart-rv-sail-switch.git
cd smart-rv-sail-switch
```

### 2. Open in CLion

1. **Open CLion**
2. **File -> Open** -> Select project folder
3. CLion will detect `platformio.ini` and configure automatically
4. Wait for PlatformIO to download dependencies

### 3. Configure PlatformIO Environment

The project has two environments in `platformio.ini`:

- **`attiny85`** - Main firmware for real hardware (default)
- **`wokwi`** - Main firmware for Wokwi simulation

**Example configuration:**
```ini
[env:attiny85]
platform = atmelavr
board = attiny85
upload_protocol = usbtiny
board_build.f_cpu = 8000000L

[env:wokwi]
platform = atmelavr
board = attiny85
framework = arduino
```

## Building the Project

### Using CLion:

1. **Select Environment**:
   - Bottom status bar -> Switch to desired env (attiny85 or wokwi)

2. **Build**:
   - **Build -> Build Project** (Ctrl+F9)
   - Or click hammer icon in toolbar

3. **Upload to Hardware**:
   - Connect USBtinyISP programmer with ATtiny85
   - **Run -> Run 'Upload'**
   - Or: PlatformIO toolbar -> Upload (arrow icon)

### Using Command Line:

```bash
# Build for ATtiny85
pio run -e attiny85

# Upload to ATtiny85
pio run -e attiny85 --target upload

# Build for simulation
pio run -e wokwi

# Clean build
pio run --target clean
```

## Running Wokwi Simulation

### Method 1: Wokwi VS Code Extension

1. Install Wokwi extension in VS Code
2. Open project in VS Code
3. Press **F1** -> "Wokwi: Start Simulator"
4. Simulation opens in browser with interactive circuit

### Method 2: Wokwi CLI

```bash
# Build firmware for simulation
pio run -e wokwi

# Run Wokwi simulator
wokwi-cli .

# Opens browser at http://localhost:9012
```

### Simulated Circuit

The `diagram.json` includes:
- **ATtiny85** microcontroller (8MHz)
- **Red LED** on PB1 (Idle/Error indicator)
- **Green LED** on PB0 (Active/Bypass indicator)
- **Slide switch** to simulate blower (12V via voltage divider to PB3)
- **Potentiometer** to simulate pressure sensor (0-5V to PB2)

**Testing in Simulation:**
1. **Power on** -> Red LED blinks (startup)
2. **Flip blower switch ON** -> System waits for pressure
3. **Turn potentiometer** -> Simulates pressure change
4. **Green LED lights** when threshold exceeded -> Relay would close

## Debugging

### Serial Monitor (Software Serial)

ATtiny85 doesn't have hardware UART, but you can add software serial for debugging:

```cpp
#include <SoftwareSerial.h>
SoftwareSerial debug(PB3, PB4);  // RX, TX

void setup() {
    debug.begin(9600);
    debug.println("System starting...");
}
```

### Logic Analyzer

For hardware debugging:
1. Connect logic analyzer to ATtiny pins
2. Monitor: PB0, PB1, PB2, PB3, PB4, PB5
3. Use PulseView or Sigrok to view signals

### Wokwi Debugging

Wokwi includes:
- **Logic Analyzer** view in browser
- **Serial Monitor**
- **Real-time variable inspection**

## Testing

### Unit Tests

Create tests in `test/` directory:

```cpp
// test/test_pressure.cpp
#include <unity.h>

void test_pressure_threshold() {
    // Your test code
    TEST_ASSERT_EQUAL(30, PRESSURE_THRESHOLD);
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_pressure_threshold);
    UNITY_END();
}

void loop() {}
```

Run tests:
```bash
pio test
```

### Hardware Testing

See [05-testing.md](05-testing.md) for full bench testing procedures.

## Troubleshooting

### "Board not found" error
- Check USBtinyISP connection
- Linux: May need udev rules
- Run: `pio device list` to verify

### Compilation errors
- Ensure PlatformIO packages downloaded: `pio pkg update`
- Check F_CPU matches fuse settings (8MHz)

### Upload failures
- Verify ATtiny85 is properly seated in breadboard/socket
- Check all ISP connections (MISO, MOSI, SCK, RESET, VCC, GND)
- Try slower upload speed: Add `upload_flags = -B 5` to platformio.ini

### Wokwi not starting
- Build firmware first: `pio run -e wokwi`
- Check `.pio/build/wokwi/firmware.hex` exists
- Ensure `wokwi.toml` points to correct path

## IDE Tips

### CLion Keyboard Shortcuts

- **Ctrl+Space**: Code completion
- **Ctrl+B**: Go to definition
- **Shift+Shift**: Search everywhere
- **Alt+Enter**: Quick fixes
- **Ctrl+Alt+L**: Reformat code

### PlatformIO Toolbar

- **Home**: PlatformIO home page
- **Build**: Compile project
- **Upload**: Flash to hardware
- **Clean**: Remove build files
- **Monitor**: Serial monitor
- **Test**: Run unit tests

## Next Steps

1. Build and upload firmware: [04-programming.md](04-programming.md)
2. Test on hardware: [05-testing.md](05-testing.md)
3. Install in RV: [06-installation.md](06-installation.md)

## Resources

- **PlatformIO Docs**: https://docs.platformio.org/
- **Wokwi Docs**: https://docs.wokwi.com/
- **ATtiny Core**: https://github.com/SpenceKonde/ATTinyCore
- **Project GitHub**: https://github.com/miclip/smart-rv-sail-switch
