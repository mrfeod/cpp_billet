project(logging)

add_library(${PROJECT_NAME}
    Logger.cpp
    )
add_library(sloth::logging ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        fmt::fmt
        spdlog::spdlog
    PRIVATE
        Qt5::Qt5
    )
target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        STATIC_OFF_LEVEL=0
        STATIC_ERROR_LEVEL=1
        STATIC_WARN_LEVEL=2
        STATIC_INFO_LEVEL=3
        STATIC_DEBUG_LEVEL=4
        STATIC_TRACE_LEVEL=5
        STATIC_LOG_LEVEL=STATIC_INFO_LEVEL # override to change static log level
    )
