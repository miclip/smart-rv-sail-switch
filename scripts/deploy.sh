#!/bin/bash
# Build and upload firmware to ATtiny85
set -e

cd "$(dirname "$0")/.."

echo "Building and uploading to ATtiny85..."
echo ""

./scripts/build.sh

echo ""
echo "Make sure:"
echo "  - USBtinyISP is connected to USB"
echo "  - ATtiny85 is in the programmer socket"
echo "  - Power is connected (if using external power)"
echo ""
read -p "Press Enter to upload or Ctrl+C to cancel..."

~/.platformio/penv/bin/pio run -e attiny85 -t upload

echo ""
echo "Deployment complete!"
