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
#include <Cylinder.h>
#include <Pyramid3.h>
#include "Scene.h"
#include "Circle.h"
#include "Quad.h"
#include "Box.h"
#include "Pyramid4.h"
#include "Cone.h"
#include "Material.h"


/**
 * Default constructor
 */
Scene::Scene(string name, int _width, int _height) {

    width = _width;
    height = _height;

    if (name == "cornell") {
        buildCornellBox();
    } else if (name == "sphere_materials") {
        buildSphereMaterials();
    } else if (name == "specular_spheres") {
        buildSpecularSpheres();
    } else if (name == "boxes") {
        buildBoxesMaterials();
    } else if (name == "cornell_holes") {
        buildCornellBoxHole();
    } else if (name == "window") {
        buildWindow();
    } else if (name == "many_lights") {
        buildManyLights();
    } else if (name == "hole") {
        buildHoleLetters();
    } else if (name == "hidden_mirror") {
        buildHiddenMirror();
    } else {
        buildTest();
    }

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

void Scene::buildSphereMaterials() {

    setCamera(Camera(Dir(0, 0.7, 0.3), Dir(1, 0, 0), Dir(0, -0.3f, 0.7),
                     Point(0, 0, -2), 1.0,  width, height, PI/3.0f));


    Sphere globalLight(5, Point(0, 0, 0));
    globalLight.setEmit(WHITE);
    addShape(globalLight);

    /*addShape(Plane(Dir(0, 0, -1), Point(0, 0, 1)));
    addShape(Plane(Dir(0, 1, 0), Point(0, -1, 0))); // Floor
    addShape(Plane(Dir(0, 0, 1), Point(0, 0, -2.1f)));
    addShape(Plane(Dir(-1, 0, 0), Point(2, 0, 0)));
    addShape(Plane(Dir(1, 0, 0), Point(2, 0, 0)));*/

    //Plane rightWall(Dir(-1, 0, 0), Point(1, 0, 0));
    Quad rightWall(Point(2, -1, 1), Point(2, -1, -3), Point(2, 1, 1));
    //rightWall.setMaterial(DIFF_G);
    addShape(rightWall);

    //Plane leftWall(Dir(1, 0, 0), Point(-1, 0, 0));
    Quad leftWall(Point(-2, -1, 1), Point(-2, -1, -3), Point(-2, 1, 1));
    //leftWall.setMaterial(DIFF_R);
    addShape(leftWall);

    //Plane floor(Dir(0, 1, 0), Point(0, -1, 0));
    Quad floor(Point(-2, -1, -3), Point(2, -1, -3), Point(-2, -1, 1));
    addShape(floor);


    //Plane bottom(Dir(0, 0, -1), Point(0, 0, 1));
    Quad bottom(Point(-2, -1, 1), Point(2, -1, 1), Point(-2, 1, 1));
    addShape(bottom);

    //Plane backWall(Dir(0, 0, 1), Point(0, 0, -3));
    Quad backWall(bottom.moveZ(-4));
    addShape(backWall);


    Sphere diffuse(0.35f, Point(-1.3f, -0.6f, 0));
    diffuse.setMaterial(Diffuse(GREEN));
    addShape(diffuse);

    Sphere specular(diffuse.moveX(0.9));
    specular.setMaterial(Specular(RED, 50));
    addShape(specular);

    Sphere reflective(specular.moveX(0.9));
    reflective.setMaterial(Reflective(WHITE));
    addShape(reflective);

    Sphere transmittive(reflective.moveX(0.9));
    transmittive.setMaterial(Transmittive(WHITE));
    transmittive.setRefractiveIndex(GLASS);
    addShape(transmittive);


}

void Scene::buildSpecularSpheres() {

    setCamera(Camera(Dir(0, 0.7, 0.3), Dir(1, 0, 0), Dir(0, -0.3f, 0.7),
                     Point(0, 0, -2), 1.0,  width, height, PI/3.0f));


    Sphere globalLight(5, Point(0, 0, 0));
    globalLight.setEmit(WHITE);
    addShape(globalLight);

    /*addShape(Plane(Dir(0, 0, -1), Point(0, 0, 1)));
    addShape(Plane(Dir(0, 1, 0), Point(0, -1, 0))); // Floor
    addShape(Plane(Dir(0, 0, 1), Point(0, 0, -2.1f)));
    addShape(Plane(Dir(-1, 0, 0), Point(2, 0, 0)));
    addShape(Plane(Dir(1, 0, 0), Point(2, 0, 0)));*/

    //Plane rightWall(Dir(-1, 0, 0), Point(1, 0, 0));
    Quad rightWall(Point(2, -1, 1), Point(2, -1, -3), Point(2, 1, 1));
    //rightWall.setMaterial(DIFF_G);
    addShape(rightWall);

    //Plane leftWall(Dir(1, 0, 0), Point(-1, 0, 0));
    Quad leftWall(Point(-2, -1, 1), Point(-2, -1, -3), Point(-2, 1, 1));
    //leftWall.setMaterial(DIFF_R);
    addShape(leftWall);

    //Plane floor(Dir(0, 1, 0), Point(0, -1, 0));
    Quad floor(Point(-2, -1, -3), Point(2, -1, -3), Point(-2, -1, 1));
    addShape(floor);


    //Plane bottom(Dir(0, 0, -1), Point(0, 0, 1));
    Quad bottom(Point(-2, -1, 1), Point(2, -1, 1), Point(-2, 1, 1));
    addShape(bottom);

    //Plane backWall(Dir(0, 0, 1), Point(0, 0, -3));
    Quad backWall(bottom.moveZ(-4));
    addShape(backWall);


    Sphere diffuse(0.35f, Point(-1.3f, -0.6f, 0));
    diffuse.setMaterial(Specular(RED, 25.0f));
    addShape(diffuse);

    Sphere specular(diffuse.moveX(0.9));
    specular.setMaterial(Specular(GREEN, 80.0f));
    addShape(specular);

    Sphere reflective(specular.moveX(0.9));
    reflective.setMaterial(Specular(BLUE, 170.0f));
    addShape(reflective);

    Sphere transmittive(reflective.moveX(0.9));
    transmittive.setMaterial(Specular(YELLOW, 250.0f));
    //transmittive.setRefractiveIndex(GLASS);
    addShape(transmittive);


}

void Scene::buildBoxesMaterials() {

    setCamera(Camera(Dir(0, 1, 0), Dir(1, 0, 0), Dir(0, 0, 1),
                     Point(0.f, -0.f, -2.8f), 1.0, width, height, PI/3.0f));

    Quad light(Point(-0.5f, 0.99f, -0.2f), Point(0.5f, 0.99f, -0.2f), Point(-0.5f , 0.99f, 0.8), Point(0.5f , 0.99f , 0.8));
    light = light.moveZ(-0.6f);
    light.setEmit(WHITE);
    addShape(light);


    //Plane rightWall(Dir(-1, 0, 0), Point(1, 0, 0));
    Quad rightWall(Point(1, -1, 1), Point(1, -1, -3), Point(1, 1, 1));
    rightWall.setMaterial(DIFF_G);
    addShape(rightWall);

    //Plane leftWall(Dir(1, 0, 0), Point(-1, 0, 0));
    Quad leftWall(Point(-1, -1, 1), Point(-1, -1, -3), Point(-1, 1, 1));
    leftWall.setMaterial(DIFF_R);
    addShape(leftWall);

    //Plane floor(Dir(0, 1, 0), Point(0, -1, 0));
    Quad floor(Point(-1, -1, -3), Point(1, -1, -3), Point(-1, -1, 1));
    addShape(floor);

    //Plane ceiling(Dir(0, -1, 0), Point(0, 1, 0));
    Quad ceiling(floor.moveY(2));
    addShape(ceiling);

    //Plane bottom(Dir(0, 0, -1), Point(0, 0, 1));
    Quad bottom(Point(-1, -1, 1), Point(1, -1, 1), Point(-1, 1, 1));
    addShape(bottom);

    //Plane backWall(Dir(0, 0, 1), Point(0, 0, -3));
    Quad backWall(bottom.moveZ(-4));
    addShape(backWall);

    Quad q(Point(0.2, -1, 0), Point(0.8, -1, 0), Point(0.2 , -1 , 0.7f));
    //q.setMaterial(Transmittive(WHITE));
    //q.setRefractiveIndex(GLASS);
    //q = q.moveX(0.5f);
    Box box(q, 0.8f);
    box.setMaterial(Transmittive(WHITE));
    box.setRefractiveIndex(GLASS);
    addAllShapes(box.getFaces());

    Box box2(box.moveX(-1));
    box2.setMaterial(Transmittive(WHITE));
    box2.setRefractiveIndex(WATER);
    addAllShapes(box2.getFaces());
    //addShape(q);


}

void Scene::buildCornellBox() {

    setCamera(Camera(Dir(0, 1, 0), Dir(1, 0, 0), Dir(0, 0, 1),
                     Point(0.f, -0.f, -2.8f), 1.0,  width, height, PI/3.0f));

    Quad light(Point(-0.5f, 0.999f, -0.2f), Point(0.5f, 0.999f, -0.2f), Point(-0.5f , 0.999f, 0.8), Point(0.5f , 0.999f , 0.8));
    light = light.moveZ(-0.6f);
    light.setEmit(WHITE);
    addShape(light);


    //Plane rightWall(Dir(-1, 0, 0), Point(1, 0, 0));
    Quad rightWall(Point(1, -1, 1), Point(1, -1, -3), Point(1, 1, 1));
    rightWall.setMaterial(DIFF_G);
    addShape(rightWall);

    //Plane leftWall(Dir(1, 0, 0), Point(-1, 0, 0));
    Quad leftWall(Point(-1, -1, 1), Point(-1, -1, -3), Point(-1, 1, 1));
    leftWall.setMaterial(DIFF_R);
    addShape(leftWall);

    //Plane floor(Dir(0, 1, 0), Point(0, -1, 0));
    Quad floor(Point(-1, -1, -3), Point(1, -1, -3), Point(-1, -1, 1));
    addShape(floor);

    //Plane ceiling(Dir(0, -1, 0), Point(0, 1, 0));
    Quad ceiling(floor.moveY(2));
    addShape(ceiling);

    //Plane bottom(Dir(0, 0, -1), Point(0, 0, 1));
    Quad bottom(Point(-1, -1, 1), Point(1, -1, 1), Point(-1, 1, 1));
    addShape(bottom);

    //Plane backWall(Dir(0, 0, 1), Point(0, 0, -3));
    Quad backWall(bottom.moveZ(-4));
    addShape(backWall);

    Sphere leftSphere(0.35f, Point(-0.5f, -0.6f, 0.6f));
    leftSphere.setMaterial(Diffuse(ORANGE));
    addShape(leftSphere);

    Sphere rightSphere(leftSphere.moveX(1.1f));
    rightSphere.setMaterial(Specular(PURPLE, 25));
    addShape(rightSphere);
}

void Scene::buildCornellBoxHole() {

    setCamera(Camera(Dir(0, 1, 0), Dir(1, 0, 0), Dir(0, 0, 1),
                     Point(0.f, -0.f, -2.8f), 1.0,  width, height, PI/3.0f));

    Sphere sky(8.75f, Point(0, 10, 0));
    //sky.setMaterial(Diffuse(RGB(0.1f, 0.6f, 0.85f)));
    sky.setEmit(WHITE);
    addShape(sky);

    Sphere sun(3, Point(0, 5, 1));
    sun.setEmit(WHITE);
    //sun.setIntensity(5.0f);
    //addShape(sun);

    //Plane rightWall(Dir(-1, 0, 0), Point(1, 0, 0));
    Quad rightWall(Point(1, -1, 1), Point(1, -1, -3), Point(1, 1, 1));
    rightWall.setMaterial(DIFF_G);
    addShape(rightWall);

    //Plane leftWall(Dir(1, 0, 0), Point(-1, 0, 0));
    Quad leftWall(Point(-1, -1, 1), Point(-1, -1, -3), Point(-1, 1, 1));
    leftWall.setMaterial(DIFF_R);
    addShape(leftWall);

    //Plane floor(Dir(0, 1, 0), Point(0, -1, 0));
    Quad floor(Point(-1, -1, -3), Point(1, -1, -3), Point(-1, -1, 1));
    addShape(floor);

    //Plane ceiling(Dir(0, -1, 0), Point(0, 1, 0));
    Quad ceiling(floor.moveY(2));
    Quad hole(Point(-0.5f, 1, -0.2f), Point(0.5f, 1, -0.2f), Point(-0.5f , 1, 0.8), Point(0.5f, 1, 0.8));
    hole = hole.moveZ(-0.6f);
    //Quad hole2(hole.moveX(0.4f));
    //Quad hole3(hole2.moveX(0.4f));
    ceiling.addHole(hole);
    //ceiling.addHole(hole2);
    //ceiling.addHole(hole3);
    addShape(ceiling);

    //Plane bottom(Dir(0, 0, -1), Point(0, 0, 1));
    Quad bottom(Point(-1, -1, 1), Point(1, -1, 1), Point(-1, 1, 1));
    addShape(bottom);

    //Plane backWall(Dir(0, 0, 1), Point(0, 0, -3));
    Quad backWall(bottom.moveZ(-4));
    addShape(backWall);

    Sphere leftSphere(0.35f, Point(-0.5f, -0.6f, 0.6f));
    leftSphere.setMaterial(Diffuse(ORANGE));
    addShape(leftSphere);

    Sphere rightSphere(leftSphere.moveX(1.1f));
    rightSphere.setMaterial(Specular(PURPLE, 25.0f));
    addShape(rightSphere);
}

void Scene::buildWindow() {

    setCamera(Camera(Dir(0, 1, 0), Dir(1, 0, 0), Dir(0, 0, 1),
                     Point(0, 0, -2.8f), 1.0,  width, height, PI/3.0f));

    Sphere light(3,Point(6.5f, 0.99f, -0.2f));
    light = light.moveZ(-0.6f);
    light.setEmit(WHITE);
    light.setIntensity(5);
    addShape(light);

    Plane backPlane(Dir(0, 0, -1),Point(0, 0, 20));
    backPlane.setMaterial(Diffuse(RGB(0, 0.25f, 1)));//azul cielo
    addShape(backPlane);
    //Plane rightWall(Dir(-1, 0, 0), Point(1, 0, 0));
    Quad rightWall(Point(1, -1, 1), Point(1, -1, -3), Point(1, 1, 1));
    //rightWall.setMaterial(DIFF_G);
    rightWall.addHole(Circle(Point(1, 0, -1),Dir(-1, 0, 0), 0.5f));
    //rightWall.addHole(Quad(Point(0.4f,-0.4f,0.4f),Point(0.4f,-0.4f,-1.5f),Point(0.4f,0.4f,0.4f)));
    addShape(rightWall);

    //Plane leftWall(Dir(1, 0, 0), Point(-1, 0, 0));
    Quad leftWall(Point(-1, -1, 1), Point(-1, -1, -3), Point(-1, 1, 1));
    leftWall.setMaterial(DIFF_R);
    addShape(leftWall);

    //Plane floor(Dir(0, 1, 0), Point(0, -1, 0));
    Quad floor(Point(-1, -1, -3), Point(1, -1, -3), Point(-1, -1, 1));
    addShape(floor);

    //Plane ceiling(Dir(0, -1, 0), Point(0, 1, 0));
    Quad ceiling(floor.moveY(2));
    addShape(ceiling);

    //Plane bottom(Dir(0, 0, -1), Point(0, 0, 1));
    Quad bottom(Point(-1, -1, 1), Point(1, -1, 1), Point(-1, 1, 1));
    addShape(bottom);

    //Plane backWall(Dir(0, 0, 1), Point(0, 0, -3));
    Quad backWall(bottom.moveZ(-4));
    addShape(backWall);

    Sphere leftSphere(0.35f, Point(-0.5f, -0.6f, 0.6f));
    leftSphere.setMaterial(DIFF_R);
    //leftSphere.setRefractiveIndex(GLASS);
    addShape(leftSphere);

    Sphere rightSphere(leftSphere.moveX(1.1f));
    rightSphere.setMaterial(MIRROR);
    addShape(rightSphere);

    //Box box1();
    // box1.setMaterial();
}

void Scene::buildManyLights() {

    setCamera(Camera(Dir(0, 1, 0), Dir(1, 0, 0), Dir(0, 0, 1),
                     Point(0.f, -0.f, -2.8f), 1.0,  width, height, PI/3.0f));

    Quad light(Point(-0.9f, 0.999f, -1), Point(-0.6f, 0.999f, -1), Point(-0.9f , 0.999f, -0.7f), Point(-0.6f , 0.999f , -0.7f));
    //light = light.moveZ(-0.6f);
    //light.setEmit(WHITE);
    //addShape(light);
    Box lightBox(light, -0.04f);
    lightBox.setEmit(WHITE);
    addAllShapes(lightBox.getFaces());
    //light.setEmit(WHITE);
    //addShape(light);

    Box lightBox2(lightBox.moveX(0.75f).moveZ(0.75f));
    lightBox2.setEmit(WHITE);
    addAllShapes(lightBox2.getFaces());

    Box lightBox3(lightBox.moveX(1.5));
    lightBox3.setEmit(WHITE);
    addAllShapes(lightBox3.getFaces());

    Box lightBox4(lightBox.moveZ(1.5));
    lightBox4.setEmit(WHITE);
    addAllShapes(lightBox4.getFaces());

    Box lightBox5(lightBox.moveX(1.5).moveZ(1.5));
    lightBox5.setEmit(WHITE);
    addAllShapes(lightBox5.getFaces());


    //Plane rightWall(Dir(-1, 0, 0), Point(1, 0, 0));
    Quad rightWall(Point(1, -1, 1), Point(1, -1, -3), Point(1, 1, 1));
    rightWall.setMaterial(DIFF_G);
    addShape(rightWall);

    //Plane leftWall(Dir(1, 0, 0), Point(-1, 0, 0));
    Quad leftWall(Point(-1, -1, 1), Point(-1, -1, -3), Point(-1, 1, 1));
    leftWall.setMaterial(DIFF_R);
    addShape(leftWall);

    //Plane floor(Dir(0, 1, 0), Point(0, -1, 0));
    Quad floor(Point(-1, -1, -3), Point(1, -1, -3), Point(-1, -1, 1));
    addShape(floor);

    //Plane ceiling(Dir(0, -1, 0), Point(0, 1, 0));
    Quad ceiling(floor.moveY(2));
    addShape(ceiling);

    //Plane bottom(Dir(0, 0, -1), Point(0, 0, 1));
    Quad bottom(Point(-1, -1, 1), Point(1, -1, 1), Point(-1, 1, 1));
    addShape(bottom);
}

void Scene::buildHoleLetters() {

    setCamera(Camera(Dir(0, 1, 0), Dir(1, 0, 0), Dir(0, 0, 1),
                     Point(0.2f, 1.3f, -11.8f), 1.0,  width, height, PI/4.0f));

    Circle light(Point(0, 8, 0), Y_AXIS * -1, 8);
    //Quad light(Point(-4, 10, -3), Point(4, 10, -3), Point(-4, 10, 3));
    light.setEmit(WHITE);
    addShape(light);

    Plane floor(Y_AXIS, Point(0, -1, 0));
    addShape(floor);

    Plane back(Z_AXIS * -1, Point(0, 0, 4));
    back.setMaterial(Diffuse(GREEN));
    addShape(back);


    /** ################################################################### **/
    Quad wall(Point(-4, -1, -3.5f), Point(4.4, -1, -3.5f), Point(-4, 2, -3.5f));

    // LETTERS
    Quad h(Point(-3.8f, -0.5f, -3.5f), Point(-3.6f, -0.5f, -3.5f), Point(-3.8f, 1.5f, -3.5f));
    Quad h2(h.moveX(1));
    Quad h3(Point(-3.8f, 0.4, -3.5f), Point(-2.6f, 0.4, -3.5f), Point(-3.8f, 0.6, -3.5f));
    wall.addHole(h);
    wall.addHole(h2);
    wall.addHole(h3);

    Circle o(Point(-1.3f, 0.5, -3.5f), Dir(0, 0, -1), 1.0);
    Circle o2(Point(-1.3f, 0.5, -3.51f), Dir(0, 0, -1), 0.8);
    wall.addHole(o);
    addShape(o2);

    Quad l(h.moveX(3.8));
    Quad l1(h3.moveX(3.8).moveY(-0.9f));
    wall.addHole(l);
    wall.addHole(l1);

    Quad e(l.moveX(1.5));
    Quad e1(l1.moveX(1.5));
    Quad e2(e1.moveY(0.9));
    Quad e3(e2.moveY(0.9));
    wall.addHole(e);
    wall.addHole(e1);
    wall.addHole(e2);
    wall.addHole(e3);

    Quad s(e1.moveX(1.5));
    Quad s1(s.moveY(0.9));
    Quad s2(s1.moveY(0.9));
    Quad s3(Point(4, -0.5f, -3.5f), Point(4.2, -0.5f, -3.5f), Point(4, 0.6, -3.5f));
    Quad s4(s3.moveX(-1).moveY(0.9));
    wall.addHole(s);
    wall.addHole(s1);
    wall.addHole(s2);
    wall.addHole(s3);
    wall.addHole(s4);

    addShape(wall);

    /** ################################################## **/
    Triangle triangle(Point(-5, -0.99f, -1), Point(-3, -0.99f, -3), Point(-1, -0.99f, -2));
    //triangle.setMaterial(Diffuse(RED));
    //addShape(triangle);
    Pyramid3 pyramid3(triangle, 4);
    pyramid3.setMaterial(Diffuse(RED));
    addAllShapes(pyramid3.getFaces());

    Sphere sphere(1, Point(5, 0, -1));
    sphere.setMaterial(Specular(BLUE, 25.0));
    addShape(sphere);

    Box box(Quad(Point(-0.5f, -0.99f, -2), Point(0.5, -0.99f, -2.5f), Point(0.8, -0.99f, -1.5f)), 4.5f);
    box.setMaterial(Diffuse(YELLOW));
    addAllShapes(box.getFaces());

}

void Scene::buildHiddenMirror() {

    setCamera(Camera(Dir(0, 1, 0), Dir(1, 0, 0), Dir(0, 0, 1),
                     Point(0, 1, -2.8f), 1.0,  width, height, PI/4.0f));


    Circle light(Point(0, 8, 0), Y_AXIS * -1, 8);
    //Quad light(Point(-4, 10, -3), Point(4, 10, -3), Point(-4, 10, 3));
    light.setEmit(WHITE);
    addShape(light);

    Plane back(Z_AXIS * -1, Point(0, 0, 2.5));
    addShape(back);

    Plane floor(Y_AXIS, Point(0, 0, 0));
    addShape(floor);

    Plane right(X_AXIS * -1, Point(3, 0, 0));
    right.setMaterial(Diffuse(ORANGE));
    addShape(right);

    Quad bottom(Point(0.5, 0, -1), Point(3, 0, -1), Point(0.5, 2, -1));
    bottom.setMaterial(Diffuse(RED));
    addShape(bottom);

    Quad leftMirror(Point(-0.8f, 0.5, 0), Point(0, 0.5, 0.8), Point(-0.8f, 1.5f, 0));
    leftMirror.setMaterial(Reflective(WHITE));
    addShape(leftMirror);

    Quad rightMirror(leftMirror.moveX(1.8f));
    rightMirror.setMaterial(Reflective(WHITE));
    addShape(rightMirror);

    Sphere sphere(0.25, Point(1.5, 0.8, 1.5));
    sphere.setMaterial(Diffuse(BLUE));
    addShape(sphere);

}

void Scene::buildTest() {

    setCamera(Camera(Dir(0, 1, 0), Dir(1, 0, 0), Dir(0, 0, 1),
                     Point(0.f, -0.f, -2.8f), 1.0,  width, height, PI/3.0f));

    Quad light(Point(-0.5f, 0.99f, -0.2f), Point(0.5f, 0.99f, -0.2f), Point(-0.5f , 0.99f, 0.4f), Point(0.5f , 0.99f , 0.4f));
    light = light.moveZ(-0.8f);
    light.setEmit(WHITE);
    addShape(light);


    //Plane rightWall(Dir(-1, 0, 0), Point(1, 0, 0));
    Quad rightWall(Point(1, -1, 1), Point(1, -1, -3), Point(1, 1, 1));
    rightWall.setMaterial(DIFF_G);
    addShape(rightWall);

    //Plane leftWall(Dir(1, 0, 0), Point(-1, 0, 0));
    Quad leftWall(Point(-1, -1, 1), Point(-1, -1, -3), Point(-1, 1, 1));
    leftWall.setMaterial(DIFF_R);
    addShape(leftWall);

    //Plane floor(Dir(0, 1, 0), Point(0, -1, 0));
    Quad floor(Point(-1, -1, -3), Point(1, -1, -3), Point(-1, -1, 1));
    addShape(floor);

    //Plane ceiling(Dir(0, -1, 0), Point(0, 1, 0));
    Quad ceiling(floor.moveY(2));
    addShape(ceiling);

    //Plane bottom(Dir(0, 0, -1), Point(0, 0, 1));
    Quad bottom(Point(-1, -1, 1), Point(1, -1, 1), Point(-1, 1, 1));
    addShape(bottom);

    //Plane backWall(Dir(0, 0, 1), Point(0, 0, -3));
    Quad backWall(bottom.moveZ(-4));
    addShape(backWall);

    Cone cone(X_AXIS, Point(0, 0, 0.5f), 0.5f);
    cone.setMaterial(Diffuse(BLUE));
    addShape(cone);

    Cylinder cylinder(Point(0, 0, 0.5f), Dir(0, 1, 0), 0.35f);
    cylinder.setMaterial(TRANSP);
    cylinder.setRefractiveIndex(GLASS);
    //addShape(cylinder);

}
