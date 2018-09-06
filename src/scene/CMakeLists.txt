set(SOURCE_FILES
        Camera.cpp
        Image.cpp
        LightSource.cpp
        Ray.cpp
        RGB.cpp
        Scene.cpp
        Material.cpp Texture.cpp)

set(HEADER_FILES
        ${PROJECT_SOURCE_DIR}/include/scene/Camera.h
        ${PROJECT_SOURCE_DIR}/include/scene/Image.h
        ${PROJECT_SOURCE_DIR}/include/scene/LightSource.h
        ${PROJECT_SOURCE_DIR}/include/scene/Ray.h
        ${PROJECT_SOURCE_DIR}/include/scene/RGB.h
        ${PROJECT_SOURCE_DIR}/include/scene/Scene.h
        ${PROJECT_SOURCE_DIR}/include/scene/Material.h
        ${PROJECT_SOURCE_DIR}/include/scene/Texture.h)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/scene
        ${PROJECT_SOURCE_DIR}/include/utils
        )

add_library(scene STATIC ${SOURCE_FILES} ${HEADER_FILES})