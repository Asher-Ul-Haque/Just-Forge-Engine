#!/bin/bash

# Function to determine the appropriate shell configuration file
get_shell_config_file() {
    local shell_name
    shell_name=$(basename "$SHELL")
    if [[ "$shell_name" == "zsh" ]]; then
        echo "$HOME/.zshrc"
    elif [[ "$shell_name" == "bash" ]]; then
        echo "$HOME/.bashrc"
    elif [[ "$shell_name" == "fish" ]]; then
        echo "$HOME/.config/fish/config.fish"
    else
        echo "$HOME/.profile"
    fi
}

# Function to install Vulkan SDK from GitHub repositories
install_vulkan_sdk() {
    echo "Installing Vulkan SDK from GitHub repositories..."

    # Clone necessary Vulkan repositories
    git clone https://github.com/KhronosGroup/Vulkan-Headers.git
    git clone https://github.com/KhronosGroup/Vulkan-Loader.git
    git clone https://github.com/KhronosGroup/Vulkan-ValidationLayers.git

    # Build and install Vulkan-Headers
    cd Vulkan-Headers
    mkdir build
    cd build
    cmake ..
    sudo make install
    cd ../..

    # Build and install Vulkan-Loader
    cd Vulkan-Loader
    mkdir build
    cd build
    cmake ..
    sudo make install
    cd ../..

    # Build and install Vulkan-ValidationLayers
    cd Vulkan-ValidationLayers
    mkdir build
    cd build
    cmake ..
    sudo make install
    cd ../..

    VULKAN_SDK_DIR="/usr/local"

    CONFIG_FILE=$(get_shell_config_file)

    echo "export VULKAN_SDK=\"$VULKAN_SDK_DIR\"" >> "$CONFIG_FILE"
    echo 'export PATH=$VULKAN_SDK/bin:$PATH' >> "$CONFIG_FILE"
    echo 'export LD_LIBRARY_PATH=$VULKAN_SDK/lib:$LD_LIBRARY_PATH' >> "$CONFIG_FILE"
    echo 'export VK_ICD_FILENAMES=$VULKAN_SDK/etc/vulkan/icd.d/nvidia_icd.json:$VULKAN_SDK/etc/vulkan/icd.d/intel_icd.x86_64.json' >> "$CONFIG_FILE"
    echo 'export VK_LAYER_PATH=$VULKAN_SDK/etc/vulkan/explicit_layer.d' >> "$CONFIG_FILE"

    source "$CONFIG_FILE"
}

# Function to install required packages for Debian-based systems
install_packages_debian() {
    echo "Updating package list and installing required packages for Debian-based systems..."
    sudo apt-get update
    sudo apt-get install -y git clang make cmake libx11-xcb-dev libxkbcommon-x11-dev wget libvulkan-dev vulkan-tools
    sudo apt-get autoremove
}

# Function to install required packages for Arch-based systems
install_packages_arch() {
    echo "Updating package list and installing required packages for Arch-based systems..."
    sudo pacman -Syu --noconfirm
    sudo pacman -S --noconfirm git clang make cmake libx11-xcb libxkbcommon-x11 wget libvulkan vulkan-tools
}

# Determine the package manager and install required packages
if command -v apt-get &> /dev/null; then
    install_packages_debian
elif command -v pacman &> /dev/null; then
    install_packages_arch
else
    echo "Unsupported package manager. Please install the required packages manually."
    exit 1
fi

# Install Vulkan SDK from GitHub repositories
install_vulkan_sdk

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
