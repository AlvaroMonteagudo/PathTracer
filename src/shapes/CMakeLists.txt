set(SOURCE_FILES
        Box.cpp
        Circle.cpp
        Cone.cpp
        Plane.cpp
        Pyramid.cpp
        Quad.cpp
        Sphere.cpp
        Triangle.cpp
        )

set(HEADER_FILES
        ${PROJECT_SOURCE_DIR}/include/shapes/Box.h
        ${PROJECT_SOURCE_DIR}/include/shapes/Circle.h
        ${PROJECT_SOURCE_DIR}/include/shapes/Cone.h
        ${PROJECT_SOURCE_DIR}/include/shapes/Plane.h
        ${PROJECT_SOURCE_DIR}/include/shapes/Pyramid.h
        ${PROJECT_SOURCE_DIR}/include/shapes/Quad.h
        ${PROJECT_SOURCE_DIR}/include/shapes/Sphere.h
        ${PROJECT_SOURCE_DIR}/include/shapes/Triangle.h
        ${PROJECT_SOURCE_DIR}/include/shapes/Shape.h
        )

include_directories(
        ${PROJECT_SOURCE_DIR}/include/algebraUtils
        ${PROJECT_SOURCE_DIR}/include/shapes/
)

add_library(shapes STATIC ${SOURCE_FILES} ${HEADER_FILES})