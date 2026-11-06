cmake_minimum_required(VERSION 3.16)
project(raytracer_weekend)

file(GLOB_RECURSE PROJECT_FILES CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
message(STATUS "Sources: ${PROJECT_FILES}\n")
add_executable(${PROJECT_NAME}
    ${PROJECT_FILES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:BUILD_DEBUG>
        $<$<CONFIG:Debug>:OUTPUT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/output/">
        $<$<CONFIG:Debug>:PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}/">
        $<$<CONFIG:Release>:BUILD_RELEASE>
        $<$<CONFIG:Release>:OUTPUT_PATH="./output/">
        $<$<CONFIG:Release>:PROJECT_DIR="./">
)