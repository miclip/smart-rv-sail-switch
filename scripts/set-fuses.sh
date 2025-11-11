#!/bin/bash
# Set ATtiny85 fuses for 8MHz internal oscillator
#
# Fuse settings:
#   LFUSE: 0x62 - 8MHz internal oscillator
#   HFUSE: 0xDF - Enable SPI programming, preserve EEPROM
#   EFUSE: 0xFF - Brown-out detection at 1.8V
#
# WARNING: Incorrect fuse settings can brick your ATtiny85!
# Only run this ONCE when setting up a new chip.

set -e

cd "$(dirname "$0")/.."

echo "⚠️  WARNING: Setting fuses on ATtiny85"
echo ""
echo "This will configure the chip for:"
echo "  - 8MHz internal oscillator"
echo "  - SPI programming enabled"
echo "  - EEPROM preserved during chip erase"
echo "  - Brown-out detection at 1.8V"
echo ""
echo "Fuse values:"
echo "  LFUSE = 0x62"
echo "  HFUSE = 0xDF"
echo "  EFUSE = 0xFF"
echo ""
echo "⚠️  ONLY RUN THIS ONCE PER CHIP!"
echo "⚠️  Incorrect fuses can brick your ATtiny85!"
echo ""
read -p "Type 'YES' to continue: " confirm

if [ "$confirm" != "YES" ]; then
    echo "Cancelled."
    exit 1
fi

echo ""
echo "Setting fuses..."
~/.platformio/penv/bin/pio run -e attiny85 -t fuses

echo ""
echo "Fuses set successfully!"
echo ""
echo "Run ./scripts/read-fuses.sh to verify"
