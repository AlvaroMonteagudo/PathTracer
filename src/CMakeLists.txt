set(SOURCE_FILES
        Tracer.cpp
        )

set(HEADER_FILES
        ${PROJECT_SOURCE_DIR}/include/Tracer.h
        )

include_directories(
        ${PROJECT_SOURCE_DIR}/include/algebraUtils
        ${PROJECT_SOURCE_DIR}/include/scene
        ${PROJECT_SOURCE_DIR}/include/shapes
        ${PROJECT_SOURCE_DIR}/include/utils
        ${PROJECT_SOURCE_DIR}/include
)

add_subdirectory(scene)
add_subdirectory(shapes)

add_library(tracer STATIC ${SOURCE_FILES} ${HEADER_FILES})

