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
#include "Pyramid4.h"
#include "Cone.h"


/**
 * Default constructor
 */
Scene::Scene() {

    Quad light(Point(-0.5f, 0.99f, -0.2f), Point(0.5f, 0.99f, -0.2f), Point(-0.5f , 0.99f, 0.8), Point(0.5f , 0.99f , 0.8));
    light = light.moveZ(-0.6f);
    light.setEmit(WHITE);

    Plane rightWall(Dir(-1, 0, 0), Point(1, 0, 0));
    //rightWall.setEmit(WHITE);
    rightWall.setMaterial(DIFF_G);

    Plane leftWall(Dir(1, 0, 0), Point(-1, 0, 0));
    leftWall.setMaterial(DIFF_R);

    Plane floor(Dir(0, 1, 0), Point(0, -1, 0));

    Plane ceiling(Dir(0, -1, 0), Point(0, 1, 0));

    Plane bottom(Dir(0, 0, -1), Point(0, 0, 1));

    Plane backWall(Dir(0, 0, 1), Point(0, 0, -3));
    backWall.setEmit(WHITE);

    Sphere leftSphere(0.35f, Point(-0.5f, -0.6f, 0.6f));
    leftSphere.setMaterial(Material(BLACK, BLUE, BLACK, BLACK, 25.0));

    Sphere rightSphere(leftSphere.moveX(1).moveY(1).moveZ(-0.4f));
    rightSphere.setMaterial(Material(BLACK, RED, BLACK, BLACK, 5.0));

    Quad quad(Point(-0.8f, -0.9f, 0.2), Point(-0.4f, -0.9f, 0.2), Point(-0.8f , -0.9f, 0.8));
    Pyramid4 box(quad, 0.7f);
    box.setMaterial(DIFF_B);

    Pyramid4 box2(box.moveX(1.2f));
    box2.setMaterial(*DIFF_R + *DIFF_B);

    Quad quad2(quad.moveX(1).moveY(1).moveZ(-0.5f));
    quad2.setMaterial(DIFF_B);

    setCamera(Camera(Dir(0, 1, 0), Dir(1, 0, 0), Dir(0, 0, 1),
                    Point(0.f, -0.f, -2.8f), 1.0, 720, 720, PI/3.0f));

    addShape(rightWall);
    addShape(leftWall);
    addShape(floor);
    addShape(ceiling);
    addShape(bottom);
    addShape(light);
    //addShape(leftSphere);
    //addShape(rightSphere);
    addAllShapes(box.getFaces());
    addAllShapes(box2.getFaces());
    //addShape(quad2);
}

/*Scene::Scene() {

    Quad light(Point(-0.4f, 0.99f, -0.8f), Point(0.4f, 0.99f, -0.8f), Point(0.4f , 0.99f, 0), Point(-0.4f , 0.99f , 0));
    light.setEmit(WHITE);

    Circle light_c(Point(0.5, -0.9f, -0.5f), Dir(0, 1, 0), 0.4f);
    light_c.setMaterial(DIFF_R);


    Plane rightWall(Dir(-1, 0, 0), Point(1, 0, 0));
    //rightWall.setEmit(WHITE);
    rightWall.setMaterial(DIFF_G);

    Plane leftWall(Dir(1, 0, 0), Point(-1, 0, 0));
    //leftWall.setEmit(WHITE);
    leftWall.setMaterial(DIFF_R);

    Plane floor(Dir(0, 1, 0), Point(0, -1, 0));

    Plane ceiling(Dir(0, -1, 0), Point(0, 1, 0));

    Plane bottom(Dir(0, 0, -1), Point(0, 0, 1));

    Plane backWall(Dir(0, 0, 1), Point(0, 0, -3));
    backWall.setEmit(WHITE);

    Sphere leftSphere(0.35f, Point(-0.5f, -0.6f, 0.6f));
    leftSphere.setMaterial(Material(BLACK, BLUE, BLACK, BLACK));

    Sphere rightSphere(0.35f, Point(0.5f, -0.6f, 0.6f));
    rightSphere.setMaterial(DIFF_B);

    Quad q(Point(-0.7f, -0.9f, -0.5f), Point(0.7f, -0.9f, -0.5f), Point(-0.7f , -0.9f , 0.7f));
    q.setMaterial(DIFF_R);

    Box box(q, 0.8f);
    box.setMaterial(DIFF_R);
    //addAllShapes(box.getFaces());

    Triangle t(Point(-0.5f, -0.9f, -0.5f), Point(0.5f, -0.9f, -0.5f), Point(-0.5f , -0.9f , 0.5f));
    t.setMaterial(DIFF_R);


    Pyramid4 pyramid4(q, 0.4f);
    pyramid4.setMaterial(DIFF_R);
    addAllShapes(pyramid4.getFaces());


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
    //addShape(light_c);
    addShape(q);
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