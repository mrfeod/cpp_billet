project(app)

add_library(${PROJECT_NAME} STATIC
    LogHandler.cpp
    LogHandler.h
    App.cpp
    App.h

    ui/QMLWindow.cpp
    ui/QMLWindow.h
    )

add_library(sloth::app ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt5::Qt5
        sloth::logging
        sloth::utils
        sloth::qtutils
    )
