#!/bin/sh

# Run to init dev environment

if [ "$(uname)" == "Darwin" ]; then
    echo "Mac version is not implemented"
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    echo "Init dev env on Linux"

    sudo apt update -y
    sudo apt upgrade -y

    sudo apt install -y clang-format-16 clang-tidy-16 gcovr cppcheck gprof graphviz
    sudo update-alternatives --install /usr/bin/clang clang-16 /usr/bin/clang-16 100
    sudo update-alternatives --install /usr/bin/clang-tidy clang-tidy-16 /usr/bin/clang-tidy-16 100
    sudo update-alternatives --install /usr/bin/clang-format clang-format-16 /usr/bin/clang-format-16 100
    sudo update-alternatives --install /usr/bin/scan-build scan-build-16 /usr/bin/scan-build-16 100

    #System dependencies
    sudo apt-get install -y \
        libudev-dev \
        libgl-dev \
        pkg-config \
        libgl1-mesa-glx \
        libgles2-mesa-dev \
        libglfw3-dev \
        libx11-xcb-dev \
        libxcb-dri3-dev \
        libxcb-icccm4-dev \
        libxcb-image0-dev \
        libxcb-keysyms1-dev \
        libxcb-randr0-dev \
        libxcb-render-util0-dev \
        libxcb-render0-dev \
        libxcb-shape0-dev \
        libxcb-sync-dev \
        libxcb-util-dev \
        libxcb-xfixes0-dev \
        libxcb-xinerama0-dev \
        libxcb-xkb-dev \
        libxkbcommon-x11-0 \
        uuid-dev \
        xorg-dev
elif [ "$(expr substr $(uname -s) 1 10)" == "CYGWIN_NT" ]; then
    echo "Init dev env on Windows"
fi

set DISPLAY=$DISPLAY
pip3 install cmake==3.25 conan==1.60.2 ninja gprof2dot
