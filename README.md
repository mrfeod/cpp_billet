# Cmake + Conan project template

### Do this first! Init dev environment
Install conan, cmake and ninja and dependencies from apt  
`tools/dev-init.sh`

### Build
Configure, build and run test using CMake  
`build.sh`

Usage:
`build.sh -m <mode> -q <path>`  
`build.sh -h`
* h - show help
* m - build <mode> is `release` or `debug`
* q - absolut <path> to Qt directory. Have to contain <path>/bin/qmake

### Code formatting
Reformat C++ and QML code  
`tools/reformat.sh`

### Test with coverage report
Works with CMake option -DSLOTH_TEST_REPORT=ON  
Prints coverage report to stdout  
`tools/test.sh`

### Static analysis
After the script has done you can find reports in `build-static-analysis/report_*` directories  
`tools/static_analysis.sh`

### Profiling
Works with CMake option -DSLOTH_PROFILING=ON. Default enabled in debug mode.  
Make `build/bin/profile-<datetime>.svg` file as result.  
`tools/profile.sh ./app`

### Package .deb
For testing purposes to deploy on clean environment .deb package very useful  
`tools/package.sh`

To run the package:
```shell
sudo apt remove app
sudo apt install app-<version>-<commit>.deb
cd /opt/lonely_sloth/app
sudo sh ./run.sh
```
