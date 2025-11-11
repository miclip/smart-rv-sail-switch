# Deployment Scripts

Scripts for building and uploading firmware to the ATtiny85 via USBtinyISP programmer.

## Prerequisites

- USBtinyISP programmer connected to USB
- ATtiny85 chip in the programmer socket
- PlatformIO installed (already configured in this project)

## Scripts

### `build.sh`
Builds the firmware for ATtiny85 and shows memory usage.

```bash
./scripts/build.sh
```

Output: `.pio/build/attiny85/firmware.hex`

### `upload.sh`
Uploads the previously built firmware to the ATtiny85.

```bash
./scripts/upload.sh
```

**Note**: Run `build.sh` first to compile the firmware.

### `deploy.sh`
Builds and uploads in one step (recommended for most use).

```bash
./scripts/deploy.sh
```

This is equivalent to running `build.sh` followed by `upload.sh`.

### `set-fuses.sh`
Sets the ATtiny85 fuses for 8MHz internal oscillator.

```bash
./scripts/set-fuses.sh
```

**WARNING**: Only run this ONCE when setting up a new chip. Incorrect fuse settings can brick your ATtiny85!

Fuse values:
- `LFUSE: 0x62` - 8MHz internal oscillator
- `HFUSE: 0xDF` - Enable SPI programming, preserve EEPROM
- `EFUSE: 0xFF` - Brown-out detection at 1.8V

### `read-fuses.sh`
Reads and displays current fuse settings from the ATtiny85.

```bash
./scripts/read-fuses.sh
```

Use this to verify fuses were set correctly.

## Typical Workflow

### First-Time Setup (New ATtiny85 Chip)
```bash
# 1. Set fuses (ONLY ONCE!)
./scripts/set-fuses.sh

# 2. Verify fuses
./scripts/read-fuses.sh

# 3. Deploy firmware
./scripts/deploy.sh
```

### Regular Development
```bash
# Just deploy (build + upload)
./scripts/deploy.sh
```

### Build Only (No Upload)
```bash
# Useful for checking memory usage or preparing for manual upload
./scripts/build.sh
```

## Troubleshooting

### "Device not found" error
- Check USBtinyISP is connected to USB
- Verify ATtiny85 is properly seated in programmer socket
- Try a different USB port or cable
- On Linux, you may need to add udev rules for USBtinyISP

### "Verification failed" error
- Check all connections between programmer and ATtiny85
- Ensure proper power supply (3-5V to ATtiny85)
- Try reducing programmer speed (already set to `-B 5` in config)

### Fuse errors
- NEVER guess at fuse values - use the provided settings
- If you brick the chip with wrong fuses, you may need a high-voltage programmer to recover
- Always run `read-fuses.sh` after `set-fuses.sh` to verify
