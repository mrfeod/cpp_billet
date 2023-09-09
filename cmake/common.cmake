# Common options
execute_process(
    COMMAND git log -1 --format=%h
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
if("${GIT_HASH}" STREQUAL "")
    set(GIT_HASH "local")
endif()

if(NOT QT_DIR)
    message(NOTICE "Define QT_DIR to use external Qt")
endif()

option(SLOTH_TEST_REPORT "Use compiler options for coverage report" OFF)

set(ENABLE_CLANG_TIDY OFF)
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    option(SLOTH_PROFILING "Enable profiling" ON)
    set(ENABLE_CLANG_TIDY ON)
endif()

option(SLOTH_CLANG_TIDY "Enable clang-tidy" ${ENABLE_CLANG_TIDY})

# For clangd code model
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# C++ options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wdangling-else -Wconversion -Wpedantic")
if(NOT SLOTH_TEST_REPORT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()
if(SLOTH_PROFILING)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
endif()
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=undefined")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=undefined")

# TODO WSL issue with stack overflow in D3D12GetInterface from libd3d12.so
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
# set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address")

# Leak sanitizer have false-positive against QML an OpenGL
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=leak")
# set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=leak")

if(SLOTH_CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY clang-tidy --config-file=${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy)
endif()

# TODO Suppression doesn't work
# set(CMAKE_CXX_CPPCHECK "cppcheck")
# set(CXX_CPPCHECK "${CXX_CPPCHECK} --enable=all,error,warning,style,performance") 
# set(CXX_CPPCHECK "${CXX_CPPCHECK} --suppress=missingIncludeSystem")
# set(CXX_CPPCHECK "${CXX_CPPCHECK} --suppress=unmatchedSuppression")
# set(CXX_CPPCHECK "${CXX_CPPCHECK} --suppress=preprocessorErrorDirective")
# set(CXX_CPPCHECK "${CXX_CPPCHECK} --suppress=*:*\.conan\*")
# set(CXX_CPPCHECK "${CXX_CPPCHECK} --suppress=*:*3rdparty\*")

if(SLOTH_TEST_REPORT)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH};${CMAKE_CURRENT_BINARY_DIR})

include(${CMAKE_CURRENT_LIST_DIR}/conan.cmake)

# Describe conan dependencies
set(USE_EXTERNAL_QT FALSE)
if(DEFINED QT_DIR)
    set(USE_EXTERNAL_QT TRUE)
endif()

if(USE_EXTERNAL_QT)
    message(NOTICE "Using Qt from ${QT_DIR}. To use conan version undef QT_DIR variable")
    file(REMOVE "${CMAKE_BINARY_DIR}/FindQt5.cmake")
    set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${QT_DIR}/lib/cmake/Qt5/")
else()
    message(NOTICE "Using Qt from conan. To use external Qt build define QT_DIR variable")
    set(CONAN_Qt qt/5.15.2 expat/2.4.2)
    set(CONAN_OPTIONS_Qt
            qt:shared=True
            qt:commercial=False
            qt:opengl=desktop
            qt:qtdeclarative=True
            qt:qtquickcontrols=True
            qt:qtquickcontrols2=True
            # qt:with_sqlite3=True
        )
endif()

set(CONAN_fmt fmt/10.1.0)
if (UNIX)
    set(CONAN_OPTIONS_fmt fmt:fPIC=True)
endif()

set(CONAN_spdlog spdlog/1.12.0)
set(CONAN_OPTIONS_spdlog spdlog:header_only=True)
add_compile_definitions(SPDLOG_FMT_EXTERNAL)

set(CONAN_doctest doctest/2.4.11)

set(CONAN_magic_enum magic_enum/0.9.3)

# Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(QT "Qt${QT_VERSION}")
