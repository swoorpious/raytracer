cmake_minimum_required(VERSION 3.16)
project(raytracer_weekend)

file(GLOB_RECURSE PROJECT_FILES CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
message(STATUS "Sources: ${PROJECT_FILES}")
add_executable(${PROJECT_NAME}
        ${PROJECT_FILES}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
