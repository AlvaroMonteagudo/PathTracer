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
    rightWall.setMaterial(RED, BLACK, BLACK, BLACK);

    Plane leftWall(Plane(Dir(1, 0, 0), Point(-1, 0, 0)));
    leftWall.setMaterial(GREEN, BLACK, BLACK, BLACK);

    Plane floor(Plane(Dir(0, 1, 0), Point(0, -1, 0)));
    floor.setMaterial(GRAY, BLACK, BLACK, BLACK);

    Plane ceiling(Plane(Dir(0, -1, 0), Point(0, 1, 0)));
    ceiling.setMaterial(GRAY, BLACK, BLACK, BLACK);

    Plane bottom(Plane(Dir(0, 0, -1), Point(0, 0, 1)));
    bottom.setMaterial(GRAY, BLACK, BLACK, BLACK);

    Plane backWall(Plane(Dir(0, 0, 1), Point(0, 0, -3)));
    backWall.setMaterial(GRAY, BLACK, BLACK, BLACK);

    Sphere leftSphere(Sphere(0.35f, Point(-0.2f, 0, 0.2f)));
    leftSphere.setMaterial(RED, BLACK, BLACK, BLACK);
    //leftSphere.setRefractiveIndex(GLASS*25);

    Sphere rightSphere(Sphere(0.35f, Point(0.f, -0.6f, 0.4f)));
    rightSphere.setMaterial(BLACK, GREEN, BLACK, BLACK);
    rightSphere.setShininess(5);
    //rightSphere.setRefractiveIndex(GLASS);

    Triangle triangle(Point(-0.9f, -0.9f, -0.5f), Point(-0.05f, -0.9f , 0.4f), Point(-0.9f , 0, 0.4f));
    triangle.setMaterial(BLACK, BLACK, BLACK, WHITE);
    triangle.setRefractiveIndex(GLASS*25);

    Triangle triangle2(Point(0.9f, -0.9f, 0), Point(0.05f, -0.9f , 0.9f), Point(0.9f , 0, 0.9f));
    triangle2.setMaterial(BLACK, BLACK, BLACK, WHITE);
    triangle2.setRefractiveIndex(GLASS*25);

    Quad quad(Point(-0.5f, -0.9f, -0.5f), Point(0.3f, -0.9f, -0.3f), Point(0.5f , -0.9f, 0.3f), Point(-0.3f , -0.9f , 0.6f));

    Pyramid pyramid4(quad, 1);
    pyramid4.setMaterial(RED, BLACK, BLACK, BLACK);

    Box box(quad, 0.6);
    box.setMaterial(RED, BLACK, BLACK, BLACK);



    /*Triangle triangle2(Point(0.8f, 0.4f, -0.3f), Point(0.8f, 0.4f , 0.5f), Point(0.8f , 0.8f , 0.1f));
    triangle.setFeatures(BLUE, BLACK, BLACK, BLACK);

    Circle circle(Point(0, -0.5f, 0.2), Dir(0, 1, 0), 0.25f);
    circle.setFeatures(BLUE, BLACK, BLACK, BLACK);




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
    addShape(box);
    //addShape(leftSphere);
    //addShape(rightSphere);
    //addShape(triangle);
    //addShape(triangle2);
    addShape(light);
    //addShape(circle);
    //addShape(backWall);
    //addShape(airSphere));
    //addShape(waterSphere));
    //addShape(glassSphere));
}

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