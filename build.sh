#!/bin/sh

preset=release

while getopts hm:q: flag
do
    case "${flag}" in
        h)
            echo "Usage : build.sh -m <mode> -q <path>"
            echo "h     show this help"
            echo "m     build <mode> is 'release' or 'debug'"
            echo "q     absolut <path> to Qt directory. Have to contain <path>/bin/qmake"
            exit 0 ;;
        m)
            preset=${OPTARG}
            echo "Using preset: ${OPTARG}" ;;
        q)
            external_qt=-DQT_DIR=${OPTARG}
            echo "Qt path: ${OPTARG}" ;;
    esac
done

cmake -G Ninja --preset linux-gcc-$preset $external_qt
cmake --build --preset build-$preset
ctest --preset test-$preset
