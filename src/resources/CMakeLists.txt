project(resources)

add_library(${PROJECT_NAME} STATIC
    ./resources.qrc
    )

add_library(sloth::resources ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "")
