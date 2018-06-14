cmake_minimum_required(VERSION 3.5)     # CMake version check
project(PathTracer)                     # Create project

add_definitions( -DPROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -fpermissive -Wall -pthread")

set (SOURCE_FILES main.cpp)

add_executable(render main.cpp)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/algebraUtils
        ${PROJECT_SOURCE_DIR}/include/scene
        ${PROJECT_SOURCE_DIR}/include/shapes
        ${PROJECT_SOURCE_DIR}/include/utils
        ${PROJECT_SOURCE_DIR}/include
)

add_subdirectory(src)

target_link_libraries(
        render
        tracer
        scene
        shapes
)