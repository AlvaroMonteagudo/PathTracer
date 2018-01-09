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
#include "LightSource.h"
#include "../shapes/Plane.h"
#include "../shapes/Sphere.h"
#include "Camera.h"
#include "AreaLight.h"

class Scene {

public:

    /**
     * Default constructor
     */
    Scene();

    /**
     * Scene constructor
     * @param filename where scene specifications are
     */
    explicit Scene(string filename);

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

    /**
     * Get shapes usd in this scene
     * @return vector with shapes of this scene
     */
    const std::vector<std::shared_ptr<Shape>> &getShapes() const;

    /**
     * Get lights usd in this scene
     * @return vector with lights of this scene
     */
    const std::vector<LightSource> &getLights() const;

    /**
     * Get area lights usd in this scene
     * @return vector with area lights of this scene
     */
    const std::vector<AreaLight> &getAreaLights() const;

private:

    /// SCENE ATTRIBUTES
    std::vector<std::shared_ptr<Shape>> shapes;

    std::vector<LightSource> lights;

    std::vector<AreaLight> areaLights;

    Camera camera;

    /// Methods to set scene features stored in a file
    void addPlane(ifstream &ifstream);

    void addSphere(ifstream &ifstream);

    void parseMaterial(const string &line, RGB &kd, RGB &ks, RGB &kr, RGB &kt);
};




