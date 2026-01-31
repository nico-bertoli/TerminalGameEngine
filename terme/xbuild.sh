#!/bin/bash

# ====================================================== create build folder
mkdir -p build
clear
cd build

# ====================================================== download nbkit if not in conan cache
if ! conan search nbkit/1.0.0@local/stable 2>/dev/null | grep -q "Package_ID"; then
    echo "Creating nbkit package from GitHub..."
    TMP_DIR=$(mktemp -d)
    git clone --depth 1 https://github.com/nico-bertoli/nbkit.git "$TMP_DIR/nbkit"
    conan create "$TMP_DIR/nbkit" --name=nbkit --version=1.0.0 --user=local --channel=stable
    rm -rf "$TMP_DIR"
fi

# ====================================================== x11 dev packages error message
conan install .. --build=missing -c tools.system.package_manager:mode=skip || {
    echo ""
    echo "=========================================="
    echo "ERROR: the xorg/system package requires X11 development packages"
    echo "=========================================="
    echo ""
    echo "Please run: sudo apt-get install libx11-xcb-dev libxcb-render0-dev libxcb-render-util0-dev libxcb-xkb-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-shape0-dev libxcb-sync-dev libxcb-xfixes0-dev libxcb-xinerama0-dev libxcb-dri3-dev uuid-dev libxcb-cursor-dev libxcb-dri2-0-dev libxcb-present-dev libxcb-composite0-dev libxcb-ewmh-dev libxcb-res0-dev libfontenc-dev libice-dev libsm-dev libxaw7-dev libxcomposite-dev libxcursor-dev libxdamage-dev libxext-dev libxfixes-dev libxi-dev libxinerama-dev libxkbfile-dev libxmu-dev libxmuu-dev libxpm-dev libxrandr-dev libxrender-dev libxres-dev libxss-dev libxt-dev libxtst-dev libxv-dev libxxf86vm-dev libxcb-glx0-dev)"
    echo ""
    exit 1
}

# ====================================================== find the conan toolchain file
if [ -f Release/generators/conan_toolchain.cmake ]; then
    CMAKE_TOOLCHAIN="Release/generators/conan_toolchain.cmake"
elif [ -f conan_toolchain.cmake ]; then
    CMAKE_TOOLCHAIN="conan_toolchain.cmake"
else
    echo "ERROR: Could not find conan_toolchain.cmake"
    exit 1
fi

# ====================================================== build
cmake .. -DCMAKE_TOOLCHAIN_FILE="$CMAKE_TOOLCHAIN" -DCMAKE_BUILD_TYPE=Release
make