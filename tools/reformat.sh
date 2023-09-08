#!/bin/bash

# Run from project root `sh ./tools/reformat.sh`

echo "Before:"
git diff --shortstat

for file in $(find ./src ./tests -iname "*.h" -o -iname "*.cpp" -o -iname "*.hpp" | grep -v "\./3rdparty\|\./build\|\./\.cache\|\./RMC2GUI")
do
    clang-format -i $file
done

qmlformat=$(find ~/ /opt -executable -type f -name qmlformat 2>/dev/null | head -1)

# find qmlformat using conan
# qmlformat=$(conan info -n package_folder --paths --package-filter $(conan search --raw qt) $(conan search --raw qt)@ | grep -Po 'package_folder:\ \K(.*package\/)*')$(conan search -q "build_type=Release" $(conan search --raw qt)@ | grep -Po "Package_ID:\ \K(.*)")/bin/qmlformat

if [ -f "$qmlformat" ]; then
    $qmlformat -i $(find . -iname "*.qml" -not -path "./build*")
fi

echo "After:"
git diff --shortstat
