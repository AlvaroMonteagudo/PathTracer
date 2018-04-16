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

    Quad light(Point(-0.4f, 0.99f, -0.4f), Point(0.4f, 0.99f, -0.4f), Point(0.4f , 0.99f, 0.4f), Point(-0.4f , 0.99f , 0.4f));
    light.setEmit(WHITE);

    // Dir es normal,
    Plane rightWall(Plane(Dir(-1, 0, 0), Point(1, 0, 0)));
    rightWall.setFeatures(RED, BLACK, BLACK, BLACK);

    Plane leftWall(Plane(Dir(1, 0, 0), Point(-1, 0, 0)));
    leftWall.setFeatures(GREEN, BLACK, BLACK, BLACK);

    Plane floor(Plane(Dir(0, 1, 0), Point(0, -1, 0)));
    floor.setFeatures(GRAY, BLACK, BLACK, BLACK);

    Plane ceiling(Plane(Dir(0, -1, 0), Point(0, 1, 0)));
    ceiling.setFeatures(GRAY, BLACK, BLACK, BLACK);

    Plane bottom(Plane(Dir(0, 0, -1), Point(0, 0, 1)));
    bottom.setFeatures(GRAY * 1.5, BLACK, BLACK, BLACK);

    Plane backWall(Plane(Dir(0, 0, 1), Point(0, 0, -3)));
    backWall.setFeatures(GRAY, BLACK, BLACK, BLACK);

    Sphere leftSphere(Sphere(0.35f, Point(0, -0.6f, 0.2f)));
    leftSphere.setFeatures(BLACK, BLACK, BLACK, WHITE);
    leftSphere.setRefractiveIndex(GLASS*25);

    Sphere rightSphere(Sphere(0.35f, Point(0.f, -0.6f, 0.4f)));
    rightSphere.setFeatures(BLACK, GREEN, BLACK, BLACK);
    rightSphere.setShininess(5);
    //rightSphere.setRefractiveIndex(GLASS);

    Triangle triangle(Point(-0.8f, -0.5f, -0.5f), Point(-0.3f, -0.5f , 0.5f), Point(-0.8f , 0.5f, 0));
    triangle.setFeatures(RED, BLACK, BLACK, BLACK);
    //triangle.setRefractiveIndex(GLASS);

    /*Triangle triangle2(Point(0.8f, 0.4f, -0.3f), Point(0.8f, 0.4f , 0.5f), Point(0.8f , 0.8f , 0.1f));
    triangle.setFeatures(BLUE, BLACK, BLACK, BLACK);

    Circle circle(Point(0, -0.5f, 0.2), Dir(0, 1, 0), 0.25f);
    circle.setFeatures(BLUE, BLACK, BLACK, BLACK);

    Box box(light, 0.6);
    box.setMaterial(BLACK, BLACK, WHITE, BLACK);

    Pyramid pyramid4(light, 1);
    pyramid4.setMaterial(BLACK, BLACK, WHITE, BLACK);

    Pyramid pyramid3(triangle, 0.5);
    pyramid4.setMaterial(BLUE, BLACK, BLACK, BLACK);

    Cone cone(circle, 0.5f);
    cone.setMaterial(BLUE, BLACK, BLACK, BLACK);*/

    setCamera(Camera(Dir(0, 1, 0), Dir(1, 0, 0), Dir(0, 0, 1),
                    Point(0.f, -0.f, -2.8f), 1.0, 720, 720, PI/3.0f));

    addShape(rightWall);
    addShape(leftWall);
    addShape(floor);
    addShape(ceiling);
    addShape(bottom);
    //addShape(cone);
    //addShape(pyramid4);
    //addShape(pyramid3);
    //addShape(box);
    //addShape(leftSphere);
    //addShape(rightSphere);
    addShape(triangle);
    //addShape(triangle2);
    addShape(light);
    //addShape(circle);
    //addShape(backWall);
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