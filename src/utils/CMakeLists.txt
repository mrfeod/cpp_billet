project(utils)

add_library(${PROJECT_NAME}
    random.cpp
    )

add_library(sloth::utils ALIAS ${PROJECT_NAME})

# target_link_libraries(${PROJECT_NAME}
#     PUBLIC
#         sloth::utils
#     )