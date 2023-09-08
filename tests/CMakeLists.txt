project(tests)

include("${CONAN_DOCTEST_ROOT}/lib/cmake/doctest.cmake")

include_directories(${CMAKE_SOURCE_DIR})

add_executable(example_test
    test/test.cpp
    )
target_link_libraries(example_test
    doctest::doctest
    fmt::fmt
    magic_enum::magic_enum
    Qt5::Qt5
    )

doctest_discover_tests(example_test)
