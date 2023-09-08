#!/bin/sh

# Run from project root `sh ./tools/test.sh`

cd build

ctest -T Test -schedule-random -j $(nproc --all)

# Works with SLOTH_TEST_REPORT=ON
gcovr -r ../src . \
    -e ".*/moc_.*" \
    -e ".*/qrc_.*" \
    -e ".*3rdparty.*"

cd ..
