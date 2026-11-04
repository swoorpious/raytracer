cmake_minimum_required(VERSION 3.16)
project(raytracer_weekend)

file(GLOB_RECURSE PROJECT_FILES CMAKE_CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
message(STATUS "Sources: ${PROJECT_FILES}")
add_executable(${PROJECT_NAME}
    ${PROJECT_FILES}
    src/app.h
)

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:BUILD_DEBUG>
        $<$<CONFIG:Debug>:OUTPUT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/output/">
        $<$<CONFIG:Release>:BUILD_RELEASE>
        $<$<CONFIG:Release>:OUTPUT_PATH="./output/">
)