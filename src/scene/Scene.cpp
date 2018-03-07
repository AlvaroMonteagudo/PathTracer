/**
 *  @file    Scene.cpp
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    18/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Implementation for scene class
 */


#include <sstream>
#include <cstring>
#include "Scene.h"
#include "Circle.h"
#include "Quad.h"
#include "Box.h"
#include "Pyramid.h"
#include "Cone.h"


/**
 * Default constructor
 */
Scene::Scene() {
    // Dir es normal,
    Plane rightWall(Plane(Dir(-1, 0, 0), Point(1, 0, 0)));
    rightWall.setFeatures(RED, BLACK, BLACK, BLACK);

    Plane leftWall(Plane(Dir(1, 0, 0), Point(-1, 0, 0)));
    leftWall.setFeatures(GREEN, BLACK, BLACK, BLACK);

    Plane floor(Plane(Dir(0, 1, 0), Point(0, -1, 0)));
    floor.setFeatures(WHITE, BLACK, BLACK, BLACK);

    Plane ceiling(Plane(Dir(0, -1, 0), Point(0, 1, 0)));
    ceiling.setFeatures(WHITE, BLACK, BLACK, BLACK);

    Plane bottom(Plane(Dir(0, 0, -1), Point(0, 0, 1)));
    bottom.setFeatures(WHITE, BLACK, BLACK, BLACK);

    Plane backWall(Plane(Dir(0, 0, 1), Point(0, 0, -2)));
    backWall.setFeatures(GRAY, BLACK, BLACK, BLACK);

    Sphere leftSphere(Sphere(0.25f, Point(-0.5f, 0, 0.4f)));
    leftSphere.setFeatures(RED, BLACK, BLACK, BLACK);

    Triangle triangle(Point(-0.5f, -0.5f, 0), Point(-0.8f, -0.5f , -0.2f), Point(-0.6f ,-0.5f , 0));
    triangle.setFeatures(GREEN, BLACK, BLACK, BLACK);

    Circle circle(Point(0, -0.5f, 0.2), Dir(0, 1, 0), 0.25f);
    circle.setFeatures(BLUE, BLACK, BLACK, BLACK);

    Quad quad(Point(0, -0.5f, 0), Point(0.4, -0.5f , -0.2f), Point(0.8 ,-0.5f , 0), Point(0.4 ,-0.5f ,0.2));
    quad.setFeatures(BLUE, BLACK, BLACK, BLACK);

    Box box(quad, 0.6);
    box.setMaterial(BLUE, BLACK, BLACK, BLACK);

    Pyramid pyramid4(quad, 1);
    pyramid4.setMaterial(BLUE, BLACK, BLACK, BLACK);

    Pyramid pyramid3(triangle, 0.5);
    pyramid4.setMaterial(BLUE, BLACK, BLACK, BLACK);

    Cone cone(circle, 0.5f);
    cone.setMaterial(BLUE, BLACK, BLACK, BLACK);

    setCamera(Camera(Dir(0, 1, 0), Dir(1, 0, 0), Dir(0, 0, 1),
                    Point(0.f, -0.f, -2.8f), 1.0, 720, 720, PI/3.0f));

    LightSource light = LightSource(Point(0.0f, 0.8f, -0.3f), 1.5f);

    lights.push_back(light);

    addShape(rightWall);
    addShape(leftWall);
    addShape(floor);
    addShape(ceiling);
    addShape(bottom);
    //addShape(cone);
    //addShape(pyramid4);
    //addShape(pyramid3);
    //addShape(box);
    addShape(leftSphere);
    //addShape(triangle);
    //addShape(quad);
    //addShape(circle);
    //addShape(backWall));
    //addShape(airSphere));
    //addShape(waterSphere));
    //addShape(glassSphere));
}


/**
 * Default constructor
 */
/*Scene::Scene() {
    // Dir es normal,
    Plane rightWall(Plane(Dir(-1, 0, 0), Point(1, 0, 0)));
    rightWall.setFeatures(GREEN, BLACK, BLACK, BLACK);

    Plane leftWall(Plane(Dir(1, 0, 0), Point(-1, 0, 0)));
    leftWall.setFeatures(RED, BLACK, BLACK, BLACK);

    Plane floor(Plane(Dir(0, 1, 0), Point(0, -1, 0)));
    floor.setFeatures(GRAY, BLACK, BLACK, BLACK);

    Plane ceiling(Plane(Dir(0, -1, 0), Point(0, 1, 0)));
    ceiling.setFeatures(GRAY, BLACK, BLACK, BLACK);

    Plane bottom(Plane(Dir(0, 0, -1), Point(0, 0, 1)));
    bottom.setFeatures(BLUE, BLACK, BLACK, BLACK);

    Plane backWall(Plane(Dir(0, 0, 1), Point(0, 0, -2)));
    backWall.setFeatures(GRAY, BLACK, BLACK, BLACK);

    Sphere leftSphere(Sphere(0.6f, Point(0, 0, 0)));
    leftSphere.setFeatures(BLACK, BLACK, BLACK, WHITE);
    leftSphere.setRefractiveIndex(20);

    Sphere rightSphere(Sphere(0.3f, Point(0.68f, -0.68f, 0.55f)));
    rightSphere.setFeatures(BLACK, BLACK, BLACK, WHITE);
    rightSphere.setRefractiveIndex(WATER);

    Sphere center(Sphere(0.3f, Point(0, -0.6f, 0.3f)));
    center.setFeatures(GREEN, BLACK, BLACK, BLACK);

    Sphere back(Sphere(0.15f, Point(0.5f, -0.2f, 0.8f)));
    back.setFeatures(BLUE, BLACK, BLACK, BLACK);

    setCamera(Camera(Dir(0, 1, 0), Dir(1, 0, 0), Dir(0, 0, 1),
                     Point(0.f, -0.f, -1.8f), 1.0, 1080, 1080, PI/3.0f));

    LightSource light = LightSource(Point(0.0f, 0.8f, -0.3f), 2.5f);

    lights.push_back(light);

    addShape(rightWall));
    addShape(leftWall));
    addShape(floor));
    addShape(ceiling));
    addShape(bottom));
    addShape(backWall));
    addShape(leftSphere));
    //addShape(rightSphere));
    //addShape(center));
    //addShape(back));
}*/


/**
 * Get camera used in this scene
 * @return camera used in this scene
 */
const Camera &Scene::getCamera() const {
    return camera;
}

/**
 * Set camera values of this scene
 * @param camera
 */
void Scene::setCamera(const Camera &camera) {
    Scene::camera = camera;
}

/**
 * Get shapes usd in this scene
 * @return vector with shapes of this scene
 */
const std::vector<std::shared_ptr<Shape>> &Scene::getShapes() const {
    return shapes;
}

/**
 * Get lights usd in this scene
 * @return vector with lights of this scene
 */
const std::vector<LightSource> &Scene::getLights() const {
    return lights;
}

/**
 * Get area lights usd in this scene
 * @return vector with area lights of this scene
 */
const std::vector<AreaLight> &Scene::getAreaLights() const {
    return areaLights;
}