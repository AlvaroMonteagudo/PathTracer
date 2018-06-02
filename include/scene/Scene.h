/**
 *  @file    Scene.h
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    18/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Header file for scene class
 *  Definition of the elements that compose a scene, within their
 *  features such as color, transittance, reflectance and specular
 *  coefficients.
 *
 *  It also generates scene from files with an specific format
 *
 */
#pragma once

#include <memory>
#include <vector>
#include <map>
#include "LightSource.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Camera.h"

class Scene {


public:

    /**
     * Default constructor
     */
    Scene(string name, int width, int height);

    /**
     * Get camera used in this scene
     * @return camera used in this scene
     */
    const Camera &getCamera() const;

    /**
     * Set camera values of this scene
     * @param camera
     */
    void setCamera(const Camera &camera);

    template <class S>
    void addShape(const S &shape) {
        shapes.push_back(make_shared<S>(shape));
    }

    template <class S>
    void addShape(const shared_ptr<S> &shape) {
        shapes.push_back(shape);
    }

    template <class S>
    void addAllShapes(const std::vector<std::shared_ptr<S>> shape_vector) {
        for (int i = 0; i < shape_vector.size(); ++i) {
            shapes.push_back(shape_vector.at(i));
        }
    }

    /**
     * Get shapes usd in this scene
     * @return vector with shapes of this scene
     */
    const std::vector<std::shared_ptr<Shape>> &getShapes() const;


private:

    /// SCENE ATTRIBUTES
    std::vector<std::shared_ptr<Shape>> shapes;

    Camera camera;

    int width, height;

    void buildCornellBox();

    void buildSphereMaterials();

    void buildSpecularSpheres();

    void buildBoxesMaterials();

    void buildTest();

    void buildCornellBoxHole();

    void buildWindow();

    void manyLights();

    void buildManyLights();

    void buildHoleLetters();

    void buildHiddenMirror();
};




