project(qtutils)

add_library(${PROJECT_NAME} STATIC
        Delayed.cpp
        hash.cpp
        RunGuard.cpp
        settings.cpp
        slumber.cpp
    )

add_library(sloth::qtutils ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        sloth::utils
        Qt5::Qt5
    )
