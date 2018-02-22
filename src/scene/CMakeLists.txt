set(SOURCE_FILES
        AreaLight.cpp
        Camera.cpp
        Image.cpp
        LightSource.cpp
        Ray.cpp
        RGB.cpp
        Scene.cpp
        )

set(HEADER_FILES
        ${PROJECT_SOURCE_DIR}/include/scene/AreaLight.h
        ${PROJECT_SOURCE_DIR}/include/scene/Camera.h
        ${PROJECT_SOURCE_DIR}/include/scene/Image.h
        ${PROJECT_SOURCE_DIR}/include/scene/LightSource.h
        ${PROJECT_SOURCE_DIR}/include/scene/Ray.h
        ${PROJECT_SOURCE_DIR}/include/scene/RGB.h
        ${PROJECT_SOURCE_DIR}/include/scene/Scene.h
        )

include_directories(
        ${PROJECT_SOURCE_DIR}/include/scene
        )

add_library(scene STATIC ${SOURCE_FILES} ${HEADER_FILES})