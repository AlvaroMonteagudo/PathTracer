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
#include <Mat.h>
#include <Mesh.h>
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

    loadSceneSamples();

    width = _width;
    height = _height;

    if (scenes.find(name) != scenes.end()) {
        (this->*scenes[name])();
    } else {
        cout << "Unable to find " << name << " as a scene. Try one of the list" << endl;
        for (auto &scene : scenes) {
            cout << "\t- " << scene.first << endl;
        }
        exit(0);
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

void Scene::addWalls() {

    Plane rightWall(Dir(-1, 0, 0), Point(1.5, 0, 0));
    //Quad rightWall(Point(1, -1, 1), Point(1, -1, -3), Point(1, 1, 1));
    rightWall.setMaterial(DIFF_G);
    addShape(rightWall);

    Plane leftWall(Dir(1, 0, 0), Point(-1.5f, 0, 0));
    //Quad leftWall(Point(-1, -1, 1), Point(-1, -1, -3), Point(-1, 1, 1));
    leftWall.setMaterial(DIFF_R);
    addShape(leftWall);

    Plane floor(Dir(0, 1, 0), Point(0, -1, 0));
    //Quad floor(Point(-1, -1, -3), Point(1, -1, -3), Point(-1, -1, 1));
    addShape(floor);

    Plane ceiling(Dir(0, -1, 0), Point(0, 1, 0));
    // Quad ceiling(floor.moveY(2));
    addShape(ceiling);

    Plane bottom(Dir(0, 0, -1), Point(0, 0, 1));
    //Quad bottom(Point(-1, -1, 1), Point(1, -1, 1), Point(-1, 1, 1));
    addShape(bottom);
}

void Scene::buildCornellBox() {
    

    setCamera(Camera(Dir(0, 1, 0), Dir(1, 0, 0), Dir(0, 0, 1),
                     Point(0.f, -0.f, -2.2f), 1.0,  width, height, PI/3.0f));

    Quad light(Point(-0.7f, 0.999f, -0.3f), Point(0.7f, 0.999f, -0.3f), Point(-0.7f , 0.999f, 0.5), Point(0.7f , 0.999f , 0.5));
    //light = light.moveZ(-0.6f);
    light.setEmit(WHITE);
    addShape(light);

    addWalls();

    Plane back(Dir(0, 0, 1), Point(0, 0, -3));
    addShape(back);

    Sphere leftSphere(0.35f, Point(-1, -0.6f, 0.6f));
    leftSphere.setMaterial(Specular(ORANGE, 25.0f));
    addShape(leftSphere);

    Sphere rightSphere(leftSphere.moveX(2));
    rightSphere.setMaterial(Reflective(SLATE_BLUE));
    addShape(rightSphere);
}

void Scene::buildCornellBoxHole() {

    setCamera(Camera(Dir(0, 1, 0), Dir(1, 0, 0), Dir(0, 0, 1),
                     Point(0.f, -0.f, -2.2f), 1.0,  width, height, PI/3.0f));

    Sphere sky(75.75f, Point(0, 80, 0));
    //Plane sky(Dir(0, -1, 0), Point(0, 50, 0));
    //sky.setMaterial(Diffuse(RGB(0.1f, 0.6f, 0.85f)));
    sky.setEmit(WHITE);
    addShape(sky);

    Sphere sun(3, Point(0, 5, 1));
    sun.setEmit(WHITE);
    //sun.setIntensity(5.0f);
    //addShape(sun);

    //Plane rightWall(Dir(-1, 0, 0), Point(1, 0, 0));
    Quad rightWall(Point(1.5, -1, 1), Point(1.5, -1, -3), Point(1.5, 1, 1));
    rightWall.setMaterial(DIFF_G);
    addShape(rightWall);

    //Plane leftWall(Dir(1, 0, 0), Point(-1, 0, 0));
    Quad leftWall(Point(-1.5f, -1, 1), Point(-1.5f, -1, -3), Point(-1.5f, 1, 1));
    leftWall.setMaterial(DIFF_R);
    addShape(leftWall);

    //Plane floor(Dir(0, 1, 0), Point(0, -1, 0));
    Quad floor(Point(-1.5f, -1, -3), Point(1.5f, -1, -3), Point(-1.5f, -1, 1));
    addShape(floor);

    //Plane ceiling(Dir(0, -1, 0), Point(0, 1, 0));
    Quad ceiling(floor.moveY(2));
    Quad hole(Point(-0.7f, 1, -0.3f), Point(0.7f, 1, -0.3f), Point(-0.7f , 1, 0.5), Point(0.7f, 1, 0.5));
    //hole = hole.moveZ(-0.6f);
    //Quad hole2(hole.moveX(0.4f));
    //Quad hole3(hole2.moveX(0.4f));
    ceiling.addHole(hole);
    //ceiling.addHole(hole2);
    //ceiling.addHole(hole3);
    addShape(ceiling);

    //Plane bottom(Dir(0, 0, -1), Point(0, 0, 1));
    Quad bottom(Point(-1.5f, -1, 1), Point(1.5, -1, 1), Point(-1.5f, 1, 1));
    addShape(bottom);

    //Plane backWall(Dir(0, 0, 1), Point(0, 0, -3));
    Quad backWall(bottom.moveZ(-4));
    addShape(backWall);

    Sphere leftSphere(0.35f, Point(-1, -0.6f, 0.6f));
    leftSphere.setMaterial(Specular(ORANGE, 25.0f));
    addShape(leftSphere);

    Sphere rightSphere(leftSphere.moveX(2));
    rightSphere.setMaterial(Reflective(SLATE_BLUE));
    addShape(rightSphere);
}

void Scene::buildSphereMaterials() {

    setCamera(Camera(Dir(0, 1, 0), Dir(1, 0, 0), Dir(0, 0, 1),
                     Point(0, -0.5f, -1.7f), 1,  width, height, PI/3.0f));


    Quad light(Point(-0.7f, 0.999f, -0.3f), Point(0.7f, 0.999f, -0.3f), Point(-0.7f , 0.999f, 0.5), Point(0.7f , 0.999f , 0.5));
    //light = light.moveZ(-0.6f);
    light.setEmit(WHITE);
    addShape(light);

    addWalls();

    Plane backWall(Dir(0, 0, 1), Point(0, 0, -3));
    addShape(backWall);

    Sphere diffuse(0.25, Point(-1, -0.75f, 0));
    diffuse.setMaterial(Specular(ROYAL_BLUE, 50));
    addShape(diffuse);

    Sphere specular(diffuse.moveX(0.66));
    specular.setMaterial(Reflective(GOLDER_ROD));
    addShape(specular);

    Sphere reflective(specular.moveX(0.66));
    reflective.setMaterial(Diffuse(CHOCOLATE));
    addShape(reflective);

    Sphere transmittive(reflective.moveX(0.66));
    transmittive.setMaterial(Transmittive(WHITE));
    transmittive.setRefractiveIndex(GLASS);
    addShape(transmittive);


}

void Scene::buildEgipcianPyramids() {

    Mat mat = Mat::rotateX(PI/10);
    setCamera(Camera(mat *Dir(0, 1, 0), mat * Dir(1, 0, 0), mat * Dir(0, 0, 1),
                     Point(0, 0, -2.2f), 1,  width, height, PI/3.0f));


    //Sphere sky(7000, Point(0, -0, 0));
    Plane sky(Z_AXIS * -1, Point(0, 0, 25));
    sky.setMaterial(Diffuse(SKY_BLUE));
    //sky.setEmit(SKY_BLUE);
    //sky.setIntensity(0.1);
    addShape(sky);

    Sphere earth(400, Point(0, -401, -2));
    earth.setMaterial(Diffuse(SANDY_BROWN * 0.6));
    addShape(earth);

    Sphere sun(100000, Point(-100002, 115000, -120000));
    sun.setEmit(WHITE);
    sun.setIntensity(5);
    addShape(sun);

    //Plane light(Y_AXIS * -1, Point(0, 0.999, 0));
    //Quad light(Point(-1, 1.999f, -0.5f), Point(1, 1.999f, -0.5f), Point(-1 , 0.999f, 0.5), Point(1 , 0.999f , 0.5));
    //light = light.moveZ(-0.6f);
    //light.setEmit(WHITE);
    //addShape(light);

    //Plane light2(Z_AXIS, Point(0, 0, -2.5f));
    //light2.setEmit(WHITE);
    //addShape(light2);

    /*Plane pe = FLOOR(-1);
    pe.setMaterial(Diffuse(RED));
    addShape(pe);
    //addShape(BOTTOM(2));*/

    Point p(-1.9f, -1.1f, 0.2);
    Quad base(p, p.moveX(1.4), p.moveZ(1.4));
    Pyramid4 pyramid4(base, 1.1);
    pyramid4.setMaterial(Diffuse(CHOCOLATE * 0.3));
    addAllShapes(pyramid4.getFaces());

    Pyramid4 py(pyramid4.moveX(1.8));
    py.setMaterial(Diffuse(CHOCOLATE * 0.4));
    addAllShapes(py.getFaces());
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

    Quad light(Point(-1.3f, 0.999f, -1), Point(-0.5f, 0.999f, -1), Point(-1.3f , 0.999f, -0.6f), Point(-0.5f , 0.999f , -0.6f));
    //light = light.moveZ(-0.6f);
    //light.setEmit(WHITE);
    //addShape(light);
    Box lightBox(light, -0.04f);
    lightBox.setEmit(WHITE);
    addAllShapes(lightBox.getFaces());
    //light.setEmit(WHITE);
    //addShape(light);

    Box lightBox2(lightBox.moveX(0.9).moveZ(0.65f));
    lightBox2.setEmit(WHITE);
    addAllShapes(lightBox2.getFaces());

    Box lightBox3(lightBox.moveX(1.8));
    lightBox3.setEmit(WHITE);
    addAllShapes(lightBox3.getFaces());

    Box lightBox4(lightBox.moveZ(1.2));
    lightBox4.setEmit(WHITE);
    addAllShapes(lightBox4.getFaces());

    Box lightBox5(lightBox.moveX(1.8).moveZ(1.2));
    lightBox5.setEmit(WHITE);
    addAllShapes(lightBox5.getFaces());


    //Plane rightWall(Dir(-1, 0, 0), Point(1, 0, 0));
    Quad rightWall(Point(1.5, -1, 1), Point(1.5, -1, -3), Point(1.5, 1, 1));
    rightWall.setMaterial(DIFF_G);
    addShape(rightWall);

    //Plane leftWall(Dir(1, 0, 0), Point(-1, 0, 0));
    Quad leftWall(Point(-1.5f, -1, 1), Point(-1.5f, -1, -3), Point(-1.5f, 1, 1));
    leftWall.setMaterial(DIFF_R);
    addShape(leftWall);

    //Plane floor(Dir(0, 1, 0), Point(0, -1, 0));
    Quad floor(Point(-1.5f, -1, -3), Point(1.5, -1, -3), Point(-1.5f, -1, 1));
    addShape(floor);

    //Plane ceiling(Dir(0, -1, 0), Point(0, 1, 0));
    Quad ceiling(floor.moveY(2));
    addShape(ceiling);

    //Plane bottom(Dir(0, 0, -1), Point(0, 0, 1));
    Quad bottom(Point(-1.5f, -1, 1), Point(1.5, -1, 1), Point(-1.5f, 1, 1));
    addShape(bottom);

    Sphere transp(0.35f, Point(0, -0.5f, 0));
    transp.setMaterial(Transmittive(WHITE));
    transp.setRefractiveIndex(GLASS);
    addShape(transp);

    Sphere diffusseYellow(0.2, Point(-1, -0.8f, -0.2f));
    diffusseYellow.setMaterial(Diffuse(YELLOW));
    addShape(diffusseYellow);

    Sphere reflectiveGreen(0.25f, Point(-0.6f, -0.4f, 0.2));
    reflectiveGreen.setMaterial(Reflective(WHITE));
    addShape(reflectiveGreen);

    Sphere specularOrange(0.25f, Point(0.9, 0.5, 0.5));
    specularOrange.setMaterial(Specular(ORANGE, 10));
    addShape(specularOrange);

    Quad base(Point(0.8, -0.8f, -0.3f), Point(1.1, -0.6f, -0.5f), Point(0.6, -0.5f, -0.1f));
    Box box(base, 0.5f);
    box.setMaterial(Transmittive(BLUE));
    box.setRefractiveIndex(GLASS);
    addAllShapes(box.getFaces());
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

void Scene::buildColorPalette() {

    int spheresInLine = 17;
    int lines = 8;
    float radius = 0.25f;

    setCamera(Camera(Dir(0, 0, 1), Dir(1, 0, 0), Dir(0, -1, 0),
                     Point(spheresInLine * 0.5f / 2 - radius, 6.5, lines * 0.5f / 2 - radius),
                     1.0,  width, height, PI/4.0f));

    Plane light(CEILING(8));
    light.setEmit(WHITE);
    addShape(light);

    Plane floor(FLOOR(0));
    addShape(floor);

    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < spheresInLine; ++j) {
            Sphere sphere = Sphere(radius, Point(j * 0.5f, 0.25, i * 0.5f));
            sphere.setMaterial(Diffuse(COLORS.at(i * spheresInLine + j)));
            addShape(sphere);
        }
    }

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

void Scene::buildTeapot() {

    /*setCamera(Camera(Dir(0, 1, 0), Dir(-1, 0, 0), Dir(0, 0, -1),
                     Point(0, 15, 60), 1.0,  width, height, PI/3.0f));*/

    Mesh mesh("../ply/teapot.ply");
    mesh.setMaterial(Reflective(WHITE));
    float maxX = mesh.maxX, maxY = mesh.maxY, maxZ = mesh.maxZ;
    float minX = mesh.minX, minY = mesh.minY, minZ = mesh.minZ;

    Mat tm = Mat::rotateX(PI / 2);
    setCamera(Camera(tm * Dir(0, 1, 0), tm * Dir(1, 0, 0), tm * Dir(0, 0, 1),
                     Point(mean(maxX, minX), maxY + 3, mean(maxZ, minZ) + 2), 1.0,  width, height, PI/2.0f));

    /*Quad light(Point(-0.7f, 2, -0.3f), Point(0.7f, 2, -0.3f), Point(-0.7f , 2, 0.5), Point(0.7f , 2 , 0.5));
    //light = light.moveZ(-0.6f);
    light.setEmit(WHITE);
    addShape(light);*/

    Sphere sky(110, Point(0, 0, 0));
    //sky.setMaterial(Diffuse(RGB(0.1f, 0.6f, 0.85f)));
    sky.setEmit(WHITE);
    addShape(sky);

    Plane rightWall(Dir(-1, 0, 0), Point(maxX + 3.5f, 0, 0));
    //Quad rightWall(Point(1, -1, 1), Point(1, -1, -3), Point(1, 1, 1));
    rightWall.setMaterial(DIFF_G);
    addShape(rightWall);

    Plane leftWall(Dir(1, 0, 0), Point(minX - 3.5f, 0, 0));
    //Quad leftWall(Point(-1, -1, 1), Point(-1, -1, -3), Point(-1, 1, 1));
    leftWall.setMaterial(DIFF_R);
    addShape(leftWall);

    Plane floor(Dir(0, 0, 1), Point(0, 0, minZ));
    //Quad floor(Point(-1, -1, -3), Point(1, -1, -3), Point(-1, -1, 1));
    addShape(floor);

    Plane bottom(Dir(0, 1, 0), Point(0, minY - 2, 0));
    //Quad bottom(Point(-1, -1, 1), Point(1, -1, 1), Point(-1, 1, 1));
    addShape(bottom);

    Plane ceiling(floor.moveZ(maxZ - minZ + 5));
    //ceiling.setEmit(WHITE);
    addShape(ceiling);

    Point p = ceiling.getPoint();
    Quad light(Point(-3, -2.3f, p.z -0.01f), Point(3, -2.3f, p.z - 0.01f), Point(-3, 0, p.z - 0.01f));
    light.setEmit(WHITE);
    addShape(light);

    Plane back(bottom.moveY(maxY - minY + 10));
    //back.setEmit(WHITE);
    addShape(back);

    //addWalls();

    //Mesh mesh("../ply/Goku.obj.ply");
    //Mesh mesh("../ply/dragon.ply");
    //mesh.setMaterial(Diffuse(RED));
    addAllShapes(mesh.getFaces());

}

void Scene::buildMesh() {

    /*setCamera(Camera(Dir(0, 1, 0), Dir(-1, 0, 0), Dir(0, 0, -1),
                     Point(0, 15, 60), 1.0,  width, height, PI/3.0f));*/

    Mesh mesh("../ply/teapot.ply");
    float maxX = mesh.maxX, maxY = mesh.maxY, maxZ = mesh.maxZ;
    float minX = mesh.minX, minY = mesh.minY, minZ = mesh.minZ;

    Mat tm = Mat::rotateX(PI / 2);
    setCamera(Camera(tm * Dir(0, 1, 0), tm * Dir(1, 0, 0), tm * Dir(0, 0, 1),
                     Point(mean(maxX, minX), maxY + 3, mean(maxZ, minZ)), 1.0,  width, height, PI/2.0f));

    /*Quad light(Point(-0.7f, 2, -0.3f), Point(0.7f, 2, -0.3f), Point(-0.7f , 2, 0.5), Point(0.7f , 2 , 0.5));
    //light = light.moveZ(-0.6f);
    light.setEmit(WHITE);
    addShape(light);*/

    Sphere sky(110, Point(0, 0, 0));
    //sky.setMaterial(Diffuse(RGB(0.1f, 0.6f, 0.85f)));
    sky.setEmit(WHITE);
    addShape(sky);

    Plane rightWall(Dir(-1, 0, 0), Point(maxX + 0.5f, 0, 0));
    //Quad rightWall(Point(1, -1, 1), Point(1, -1, -3), Point(1, 1, 1));
    rightWall.setMaterial(DIFF_G);
    //addShape(rightWall);

    Plane leftWall(Dir(1, 0, 0), Point(minX - 0.5f, 0, 0));
    //Quad leftWall(Point(-1, -1, 1), Point(-1, -1, -3), Point(-1, 1, 1));
    leftWall.setMaterial(DIFF_R);
    //addShape(leftWall);

    Plane floor(Dir(0, 1, 0), Point(0, minY - 0.5f, 0));
    //Quad floor(Point(-1, -1, -3), Point(1, -1, -3), Point(-1, -1, 1));
    addShape(floor);

    /*Plane bottom(Dir(0, 0, -1), Point(0, 0, 1));
    //Quad bottom(Point(-1, -1, 1), Point(1, -1, 1), Point(-1, 1, 1));
    addShape(bottom);

    Plane back(Dir(0, 0, 1), Point(0, 0, -3));
    back.setEmit(WHITE);
    addShape(back);*/

    //addWalls();

    //Mesh mesh("../ply/Goku.obj.ply");
    //Mesh mesh("../ply/dragon.ply");
    //mesh.setMaterial(Diffuse(RED));
    addAllShapes(mesh.getFaces());

}
