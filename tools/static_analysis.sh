#!/bin/sh

# Run from project root `sh ./tools/static_analysis.sh`

export CCACHE_DISABLE=1

# Clean existing build directly if present.
# A full rebuild is preferable to have a stable output.
builddir=build-static-analysis
rm -rf $builddir

# --- clang Static Analysis ---
# Running CMake with scan-build
scan-build --use-cc=clang --use-c++=clang++ cmake -H. -B$builddir -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Building with Make and scan-build
# -j is here to speed up a little the process by parallelizing it.
scan-build --use-cc=clang --use-c++=clang++ --exclude "\.conan" -o $builddir/report_clang make -C $builddir -j$(nproc --all)

# --- cppcheck Static Analysis ---
cd $builddir

# Filter generated sources from compile commands
python3 -c "import json; input_dict = json.load(open('compile_commands.json')); output_dict = [x for x in input_dict if '_autogen' not in x['file']]; json.dump(output_dict, open('filtered_compile_commands.json', 'w'))"

# Run analyzer with suppressions of dependencies
cppcheck --project=filtered_compile_commands.json --enable=all \
    --suppress=missingIncludeSystem \
    --suppress=unmatchedSuppression \
    --suppress=unusedFunction \
    --suppress=*:*\.conan\* \
    --suppress=*:*3rdparty\* \
    --xml --xml-version=2 2>cppcheck_report.xml

# Generate report
cppcheck-htmlreport  --file=cppcheck_report.xml --title=cmake_project --report-dir=report_cppcheck --source-dir=..
