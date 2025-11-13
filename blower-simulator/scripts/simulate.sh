#!/bin/bash
# Run Wokwi simulation and open browser
cd "$(dirname "$0")/.."

echo "Starting Wokwi simulation..."
echo "Building firmware first..."
~/.platformio/penv/bin/pio run -e wokwi

echo ""
echo "Starting simulation server..."
echo "Open browser to: http://localhost:9012"
echo ""
echo "Press Ctrl+C to stop simulation"
echo ""

export WOKWI_CLI_TOKEN=wok_MFVLOExXmOlEp04peq65IdyymTIKISa051185b2f
~/.wokwi/bin/wokwi-cli .
