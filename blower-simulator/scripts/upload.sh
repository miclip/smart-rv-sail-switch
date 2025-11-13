#!/bin/bash
# Upload blower simulator firmware to ATtiny85
set -e

cd "$(dirname "$0")/.."

echo "Uploading blower simulator to ATtiny85 via USBtinyISP..."
echo "Make sure:"
echo "  - USBtinyISP is connected to USB"
echo "  - ATtiny85 is in the programmer socket"
echo "  - Power is connected"
echo ""
read -p "Press Enter to continue or Ctrl+C to cancel..."

~/.platformio/penv/bin/pio run -e attiny85 -t upload

echo ""
echo "Upload complete!"
