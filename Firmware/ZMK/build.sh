#!/bin/bash

# ZMK Build Script for Custom 60% Keyboard
# This script automates the ZMK build process

set -e  # Exit on any error

echo "🔨 ZMK Build Script for Custom 60% Keyboard"
echo "=============================================="

# Color definitions
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Check if we're in the right directory
if [ ! -f "build.yaml" ]; then
    echo -e "${RED}❌ Error: build.yaml not found. Please run this script from the zmk-config directory.${NC}"
    exit 1
fi

echo -e "${BLUE}📁 Current directory: $(pwd)${NC}"

# Check if west is installed
if ! command -v west &> /dev/null; then
    echo -e "${RED}❌ Error: 'west' command not found.${NC}"
    echo "Please install west: pip3 install --user west"
    exit 1
fi

echo -e "${GREEN}✅ West command found${NC}"

# Step 1: Initialize workspace if not already done
if [ ! -d ".west" ]; then
    echo -e "${YELLOW}🔧 Initializing ZMK workspace...${NC}"
    west init -l config/
    echo -e "${GREEN}✅ Workspace initialized${NC}"
else
    echo -e "${GREEN}✅ Workspace already initialized${NC}"
fi

# Step 2: Update dependencies
echo -e "${YELLOW}📦 Updating ZMK dependencies...${NC}"
west update

# Step 3: Export Zephyr environment
echo -e "${YELLOW}🌍 Setting up Zephyr environment...${NC}"
west zephyr-export

# Step 4: Build the firmware
echo -e "${YELLOW}🔨 Building firmware for Custom 60% keyboard...${NC}"
echo "Board: seeeduino_xiao_ble"
echo "Shield: id1"
echo ""

west build -p -b seeeduino_xiao_ble -- -DSHIELD=id1

# Check if build was successful
if [ $? -eq 0 ]; then
    echo ""
    echo -e "${GREEN}🎉 BUILD SUCCESSFUL!${NC}"
    echo ""
    echo -e "${BLUE}📦 Firmware location:${NC}"
    echo "   $(pwd)/build/zephyr/zmk.uf2"
    echo ""
    echo -e "${BLUE}📏 Firmware size:${NC}"
    ls -lh build/zephyr/zmk.uf2
    echo ""
    echo -e "${YELLOW}🚀 Next steps:${NC}"
    echo "1. Double-tap reset button on your XIAO nRF52840"
    echo "2. Copy zmk.uf2 to the mounted drive:"
    echo "   cp build/zephyr/zmk.uf2 /media/\$(whoami)/XIAO-SENSE/"
    echo ""
    echo -e "${BLUE}💡 Optional: Copy firmware to home directory${NC}"
    echo "cp build/zephyr/zmk.uf2 ~/custom60_firmware_$(date +%Y%m%d_%H%M%S).uf2"
    echo ""
else
    echo ""
    echo -e "${RED}❌ BUILD FAILED!${NC}"
    echo ""
    echo -e "${YELLOW}🔍 Common issues and solutions:${NC}"
    echo "1. Missing Zephyr SDK - install from ZMK documentation"
    echo "2. Missing dependencies - run: pip3 install -r zephyr/scripts/requirements.txt"
    echo "3. PCF8575 driver issues - this is expected (requires custom driver)"
    echo ""
    echo "Check BUILD_INSTRUCTIONS.md for detailed troubleshooting"
    exit 1
fi
