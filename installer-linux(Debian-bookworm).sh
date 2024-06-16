#!/bin/bash

# Update package list and install required packages
echo "Updating package list and installing required packages..."
sudo apt-get update
sudo apt-get install -y git clang make libx11-xcb-dev libxkbcommon-x11-dev

# Clone the specified GitHub repository
echo "Cloning the Just-Forge-Engine repository..."
git clone -b Just-Forge-3D https://github.com/Asher-Ul-Haque/Just-Forge-Engine.git

# Change directory into the cloned repository
cd Just-Forge-Engine || { echo "Failed to enter the Just-Forge-Engine directory"; exit 1; }

# Make the build script executable
echo "Making build-all.sh executable..."
chmod +x build-all.sh

# Run the build script
echo "Running build-all.sh..."
./build-all.sh

# Change directory into the build directory
cd build || { echo "Failed to enter the build directory"; exit 1; }

# Run the Just_Forge_Tester program
echo "Running Just_Forge_Tester..."
./Just_Forge_Tester
