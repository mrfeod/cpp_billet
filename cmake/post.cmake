message(STATUS "Commit: ${GIT_HASH}")
message(STATUS "Option SLOTH_TEST_REPORT: ${SLOTH_TEST_REPORT}")
if(SLOTH_PROFILING)
    message(STATUS "Option SLOTH_PROFILING: ${SLOTH_PROFILING}")
endif()
message(STATUS "Option SLOTH_CLANG_TIDY: ${SLOTH_CLANG_TIDY}")