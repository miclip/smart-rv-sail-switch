#!/bin/bash
# Read current fuse settings from ATtiny85
set -e

cd "$(dirname "$0")/.."

echo "Reading fuses from ATtiny85..."
echo ""

# Use avrdude directly to read fuses
avrdude -c usbtiny -p attiny85 -U lfuse:r:-:h -U hfuse:r:-:h -U efuse:r:-:h

echo ""
echo "Expected values for 8MHz internal oscillator:"
echo "  LFUSE: 0x62"
echo "  HFUSE: 0xDF"
echo "  EFUSE: 0xFF"
