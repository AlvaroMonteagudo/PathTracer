set(SOURCE_FILES
        Box.cpp
        Circle.cpp
        Cone.cpp
        Plane.cpp
        Pyramid4.cpp
        Quad.cpp
        Sphere.cpp
        Triangle.cpp
        Pyramid3.cpp
        Cylinder.cpp
        MeshTriangle.cpp
        Mesh.cpp)

set(HEADER_FILES
        ${PROJECT_SOURCE_DIR}/include/shapes/Box.h
        ${PROJECT_SOURCE_DIR}/include/shapes/Circle.h
        ${PROJECT_SOURCE_DIR}/include/shapes/Cone.h
        ${PROJECT_SOURCE_DIR}/include/shapes/Plane.h
        ${PROJECT_SOURCE_DIR}/include/shapes/Pyramid4.h
        ${PROJECT_SOURCE_DIR}/include/shapes/Quad.h
        ${PROJECT_SOURCE_DIR}/include/shapes/Sphere.h
        ${PROJECT_SOURCE_DIR}/include/shapes/Triangle.h
        ${PROJECT_SOURCE_DIR}/include/shapes/Shape.h
        ${PROJECT_SOURCE_DIR}/include/shapes/Pyramid3.h
        ${PROJECT_SOURCE_DIR}/include/shapes/Cylinder.h
        ${PROJECT_SOURCE_DIR}/include/shapes/MeshTriangle.h
        ${PROJECT_SOURCE_DIR}/include/shapes/Mesh.h)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/algebraUtils
        ${PROJECT_SOURCE_DIR}/include/shapes
)

add_library(shapes STATIC ${SOURCE_FILES} ${HEADER_FILES})