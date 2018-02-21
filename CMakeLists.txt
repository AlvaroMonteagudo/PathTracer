cmake_minimum_required(VERSION 3.5)     # CMake version check
project(IG)                             # Create project

set(CMAKE_CXX_STANDARD 14)              # Enable c++11 standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -fpermissive -Wall -pthread")

set (SOURCE_FILES main.cc
        include/algebraUtils/Dir.h include/algebraUtils/Mat.h include/algebraUtils/Point.h include/shapes/Shape.h
        include/shapes/Plane.h src/shapes/Plane.cpp
        include/shapes/Sphere.h src/shapes/Sphere.cpp
        include/scene/Ray.h src/scene/Ray.cpp
        include/scene/Camera.h src/scene/Camera.cpp
        include/scene/RGB.h src/scene/RGB.cpp
        include/scene/Image.h src/scene/Image.cpp
        include/scene/Scene.h src/scene/Scene.cpp
        include/scene/LightSource.h src/scene/LightSource.cpp
        include/Tracer.h src/Tracer.cpp include/shapes/Triangle.h src/shapes/Triangle.cpp include/scene/AreaLight.h src/scene/AreaLight.cpp include/samplingUtils.h include/shapes/Circle.h src/shapes/Circle.cpp include/shapes/Quad.h src/shapes/Quad.cpp include/shapes/Box.h src/shapes/Box.cpp include/shapes/Pyramid.h src/shapes/Pyramid.cpp)                        # Add main.cc file of project root directory as source file

add_executable(render ${SOURCE_FILES})