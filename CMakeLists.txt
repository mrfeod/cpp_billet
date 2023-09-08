cmake_minimum_required(VERSION 3.5)
project(cmake_project VERSION 1.0.0)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_compile_definitions(SLOTH_DEBUG)
    message(STATUS "SLOTH Debug build")
endif()

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")
set(CMAKE_INSTALL_RPATH "../lib")
message(STATUS "Install directory: ${CMAKE_INSTALL_PREFIX}")

include(cmake/common.cmake)

conan_cmake_run(
    REQUIRES
        ${CONAN_Qt}
        ${CONAN_fmt}
        ${CONAN_spdlog}
        ${CONAN_doctest}
        ${CONAN_magic_enum}
    BASIC_SETUP
    CMAKE_TARGETS
    UPDATE
    OPTIONS
        ${CONAN_OPTIONS_Qt}
        ${CONAN_OPTIONS_udev}
        ${CONAN_OPTIONS_fmt}
        ${CONAN_OPTIONS_spdlog}
    BUILD
        missing
    GENERATORS
        cmake_paths
        cmake_find_package
    )

# Qt
set(QT_COMPONENTS "Core;Gui;Network;Concurrent;Widgets;Qml;Quick;QuickControls2;SerialPort;Sql;PrintSupport")
find_package(${QT} COMPONENTS ${QT_COMPONENTS} REQUIRED)
if(USE_EXTERNAL_QT)
    set(QML_IMPORT_PATH "${QT_DIR}/qml")
    set(QT_PLUGINS_PATH "${QT_DIR}/plugins")
    add_library(${QT}::${QT} INTERFACE IMPORTED)
    foreach(component ${QT_COMPONENTS})
        set(QT_LIBS "${QT}::${component};${QT_LIBS}")
    endforeach()
    set_property(TARGET ${QT}::${QT} PROPERTY INTERFACE_LINK_LIBRARIES ${QT_LIBS})
else()
    set(QT_DIR "${${QT}_Core_LIB_DIRS}/..")
    set(QML_IMPORT_PATH "${QT_DIR}/bin/archdatadir/qml")
    set(QT_PLUGINS_PATH "${QT_DIR}/bin/archdatadir/plugins")
endif()

set(${QT}_DIR "${QT_DIR}/bin")

# Common dependencies
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(doctest REQUIRED)
find_package(magic_enum REQUIRED)

include_directories(
    ${CONAN_INCLUDE_DIRS}
    src
    tests
    )

link_libraries(stdc++fs)

# Internal libraries
add_subdirectory(3rdparty)
add_subdirectory(src/resources)
add_subdirectory(src/utils)
add_subdirectory(src/utils/logging)
add_subdirectory(src/utils/qt)
add_subdirectory(src/app)

# App executable
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        sloth::resources
        sloth::app
    )
target_link_options(${PROJECT_NAME}
    PRIVATE
        -static-libgcc
        -static-libstdc++
    )

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(${PROJECT_NAME}_DEBUG_DEFINES
    )
else() # Any Release type
    set(${PROJECT_NAME}_RELEASE_DEFINES
        QT_NO_DEBUG_OUTPUT
    )
endif()

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        QT_DEPRECATED_WARNINGS
        ${${PROJECT_NAME}_DEBUG_DEFINES}
        ${${PROJECT_NAME}_RELEASE_DEFINES}
    )

# Tests
enable_testing()
add_subdirectory(tests)

# Install
include(cmake/install.cmake)

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "lonelySloth")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${CMAKE_PROJECT_VERSION})
set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${GIT_HASH})
message(STATUS "Package name: ${CPACK_PACKAGE_FILE_NAME}")
set(CPACK_PACKAGING_INSTALL_PREFIX "/opt/lonelySloth/app")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libxcb-xinerama0")
include(CPack)

# Last actions
include(cmake/post.cmake)
