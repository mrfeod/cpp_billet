#!/bin/bash

# Run from project root `sh ./tools/profile.sh ./cmake_project`

cd build/bin

set -x

$1
out=profile-$(date '+%Y-%m-%d-%H-%M-%S').svg
gprof $1 | gprof2dot -w -s | dot -Tsvg -o "$out"

set +x
echo "Profiled: $(pwd)/$out"

cd -
