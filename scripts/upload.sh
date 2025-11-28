#!/bin/bash
# Upload firmware to ATtiny85 via USBtinyISP
set -e

cd "$(dirname "$0")/.."

echo "Uploading to ATtiny85 via USBtinyISP..."
~/.platformio/penv/bin/pio run -e attiny85 -t upload

echo ""
echo "Upload complete!"
