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

    Quad light(Point(-0.4f, 0.99f, -0.8f), Point(0.4f, 0.99f, -0.8f), Point(0.4f , 0.99f, 0), Point(-0.4f , 0.99f , 0));
    light.setEmit(WHITE);

    Circle light_c(Point(0, -0.9f, -0.5f), Dir(0, -1, 0), 0.5f);
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
    leftSphere.setShininess(5.0f);

    Sphere rightSphere(0.35f, Point(0.5f, -0.6f, 0.6f));
    rightSphere.setMaterial(DIFF_B);

    Quad q(Point(-0.5f, -0.9f, -0.5f), Point(0.5f, -0.9f, -0.5f), Point(-0.5f , -0.9f , 0.5f));
    q.setMaterial(DIFF_R);

    Triangle t(Point(-0.5f, -0.9f, -0.5f), Point(0.5f, -0.9f, -0.5f), Point(-0.5f , -0.9f , 0.5f));
    t.setMaterial(DIFF_R);

    /*Dir normal = q.getNormal();

    Point b1, b2, b3, b4;

    tie(b1, b2, b3, b4) = q.getCorners();

    Point t1 = b1 + normal * -0.6;
    Point t2 = b2 + normal * -0.6;
    Point t3 = b3 + normal * -0.6;
    Point t4 = b4 + normal * -0.6;

    Quad q1(Quad(t1, t2, t3, t4));
    q1.setMaterial(MIRROR);
    Quad q2(Quad(b1, b2, t2, t1));
    q2.setMaterial(MIRROR);
    Quad q3(Quad(b2, b3, t3, t2));
    q3.setMaterial(MIRROR);
    Quad q4(Quad(b3, b4, t4, t3));
    q4.setMaterial(MIRROR);
    Quad q5(Quad(b4, b1, t1, t4));
    q5.setMaterial(MIRROR);

    //addShape(q);
    addShape(q1);
    addShape(q2);
    addShape(q3);
    //addShape(q4);
    addShape(q5);*/

    /*Pyramid pyramid4(q, 0.6f);
    pyramid4.setMaterial(DIFF_R);
    for (const auto &i : pyramid4.getFaces()) {
        addShape(i);
    }*/


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
    addShape(light_c);
    //addShape(quad2);
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