#!/bin/bash
# Build blower simulator firmware
set -e

cd "$(dirname "$0")/.."

echo "Building blower simulator firmware for ATtiny85..."
~/.platformio/penv/bin/pio run -e attiny85

echo ""
echo "Build complete!"
echo "Firmware: .pio/build/attiny85/firmware.hex"
~/.platformio/penv/bin/pio run -e attiny85 -t size
