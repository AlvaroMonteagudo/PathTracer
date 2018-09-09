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
 *  Definition of the elements that compose a scene,  within their
 *  features such as color,  transittance,  reflectance and specular
 *  coefficients.
 *
 *  It also generates scene from files with an specific format
 *
 */
#pragma once

#include <memory>
#include <vector>
#include <random>
#include <map>
#include "LightSource.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Camera.h"
#include <functional>

using namespace std;

class Scene {


public:

    map<string, void (Scene::*)()> scenes;

    /**
     * Default constructor
     */
    Scene(string name,  int width,  int height);

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

    void loadSceneSamples() {
        scenes["cornell"] = &Scene::buildCornellBox;
        scenes["spheres"] = &Scene::buildSphereMaterials;
        scenes["cornell_hole"] = &Scene::buildCornellBoxHole;
        scenes["boxes"] = &Scene::buildBoxes;
        scenes["pyramids"] = &Scene::buildEgipcianPyramids;
        scenes["palette"] = &Scene::buildColorPalette;
        scenes["mesh"] = &Scene::buildMesh;
        scenes["teapot"] = &Scene::buildTeapot;
        scenes["test"] = &Scene::buildTest;
        scenes["lights"] = &Scene::buildManyLights;
        scenes["circles"] = &Scene::buildCornellCircle;
        scenes["holes"] = &Scene::buildHoleLetters;
        scenes["cylinders"] = &Scene::buildCylinders;
    }

    /**
     * Get shapes usd in this scene
     * @return vector with shapes of this scene
     */
    const std::vector<std::shared_ptr<Shape>> &getShapes() const;

    const std::vector<RGB> COLORS = { MAROON, DARK_RED, BROWN, FIREBRICK, CRIMSON, RED, TOMATO, CORAL, INDIAN_RED,
                                      LIGHT_CORAL, DARK_SALMON, SALMON, LIGHT_SALMON, ORANGE_RED, DARK_ORANGE,
                                      ORANGE, GOLD, DARK_GOLDEN_ROD, GOLDER_ROD, PALE_GOLDEN_ROD, DARK_KHAKI,
                                      KHAKI, OLIVE, YELLOW, YELLOW_GREEN, DARK_OLIVE_GREEN, OLIVE_DRAB, LAWN_GREEN,
                                      CHART_REUSE, GREEN_YELLOW, DARK_GREEN, GREEN, FOREST_GREEN, LIME, LIME_GREEN,
                                      LIGHT_GREEN, PALE_GREEN, DARK_SEA_GREEN, MEDIUM_SPRING_GREEN, SPRING_GREEN,
                                      SEA_GREEN, MEDIUM_AQUA_MARINE, MEDIUM_SEA_GREEN, LIGHT_SEA_GREEN,
                                      DARK_SLATE_GRAY, TEAL, DARK_CYAN, AQUA, CYAN, LIGHT_CYAN, DARK_TURQUOISE,
                                      TURQUOISE, MEDIUM_TURQUOISE, PALE_TURQUOISE, AQUA_MARINE, POWDER_BLUE,
                                      CADET_BLUE, STEEL_BLUE, CORN_FLOWER_BLUE, DEEP_SKY_BLUE, DODGER_BLUE,
                                      LIGHT_BLUE, SKY_BLUE, LIGHT_SKY_BLUE, MIDNIGHT_BLUE, NAVY, DARK_BLUE,
                                      MEDIUM_BLUE, BLUE, ROYAL_BLUE, BLUE_VIOLET, INDIGO, DARK_SLATE_BLUE,
                                      SLATE_BLUE, MEDIUM_SLATE_BLUE, MEDIUM_PURPLE, DARK_MAGENTE, DARK_VIOLET,
                                      DARK_ORCHID, MEDIUM_ORCHID, PURPLE, THISTLE, PLUM, VIOLET, MAGENTA, ORCHID,
                                      MEDIUM_VIOLET_RED, PALE_VIOLET_RED, DEEP_PINK, HOT_PINK, LIGHT_PINK, PINK,
                                      ANTIQUE_WHITE, BEIGE, BISQUE, BLANCHED_ALMOND, WHEAT, CORN_SILK, LEMON_CHIFFON,
                                      LIGHT_GOLDEN_YELLOW, LIGHT_YELLOW, SANDLE_BROWN, SIENNA, CHOCOLATE, PERU,
                                      SANDY_BROWN, BURLY_WOOD, TAN, ROSY_BROWN, MOCCASIN, NAVAJO_WHITE, PEACH_PUFF,
                                      MISTY_ROSE, LAVENDER_BLUSH, LINEN, OLD_LACE, PAPAYA_WHIP, SEA_SHELL, MINC_CREAM,
                                      SLATE_GRAY, LIGHT_SLATE_GRAY, LIGHT_STEEL_BLUE, LAVENDER, FLORAL_WHITE,
                                      ALICE_BLUE, GHOST_WHITE, HONEYDEW, IVORY, AZURE, SNOW, DIM_GRAY, GRAY,
                                      DARK_GRAY, SILVER, LIGHT_GRAY, GAINSBORG, WHITE };



        const std::vector<RGB> VIVID = {MAROON, DARK_RED, BROWN, FIREBRICK, CRIMSON, RED, TOMATO, CORAL, INDIAN_RED,
                                     LIGHT_CORAL, DARK_SALMON, SALMON, LIGHT_SALMON, ORANGE_RED, DARK_ORANGE,
                                     ORANGE, GOLD, DARK_GOLDEN_ROD, GOLDER_ROD, PALE_GOLDEN_ROD, DARK_KHAKI,
                                     KHAKI, OLIVE, YELLOW, YELLOW_GREEN, DARK_OLIVE_GREEN, OLIVE_DRAB, LAWN_GREEN,
                                     CHART_REUSE, GREEN_YELLOW, DARK_GREEN, GREEN, FOREST_GREEN, LIME, LIME_GREEN,
                                     LIGHT_GREEN, PALE_GREEN, DARK_SEA_GREEN, MEDIUM_SPRING_GREEN, SPRING_GREEN,
                                     SEA_GREEN, MEDIUM_AQUA_MARINE, MEDIUM_SEA_GREEN, LIGHT_SEA_GREEN,
                                     DARK_SLATE_GRAY, TEAL, DARK_CYAN, AQUA, CYAN, LIGHT_CYAN, DARK_TURQUOISE,
                                     TURQUOISE, MEDIUM_TURQUOISE, PALE_TURQUOISE, AQUA_MARINE, POWDER_BLUE,
                                     CADET_BLUE, STEEL_BLUE, CORN_FLOWER_BLUE, DEEP_SKY_BLUE, DODGER_BLUE,
                                     LIGHT_BLUE, SKY_BLUE, LIGHT_SKY_BLUE, MIDNIGHT_BLUE, NAVY, DARK_BLUE,
                                     MEDIUM_BLUE, BLUE, ROYAL_BLUE, BLUE_VIOLET, INDIGO, DARK_SLATE_BLUE,
                                     SLATE_BLUE, MEDIUM_SLATE_BLUE, MEDIUM_PURPLE, DARK_MAGENTE, DARK_VIOLET,
                                     DARK_ORCHID, MEDIUM_ORCHID, PURPLE, THISTLE, PLUM, VIOLET, MAGENTA, ORCHID,
                                     MEDIUM_VIOLET_RED, PALE_VIOLET_RED, DEEP_PINK, HOT_PINK, LIGHT_PINK, PINK};

private:

    /// SCENE ATTRIBUTES
    std::vector<std::shared_ptr<Shape>> shapes;

    Camera camera;

    int width, height;

    static float randFloat(float a, float b) {
        random_device device;
        mt19937 mt(device());
        uniform_real_distribution<float> generator(a, b);
        return generator(mt);
    }

    void buildCornellBox();

    void buildSphereMaterials();

    void buildSpecularSpheres();

    void buildBoxes();

    void buildTest();

    void buildCornellBoxHole();

    void buildWindow();

    void buildManyLights();

    void buildHoleLetters();

    void buildHiddenMirror();

    void addWalls();

    void buildEgipcianPyramids();

    void buildColorPalette();

    void buildMesh();

    void buildTeapot();

    void buildCornellCircle();

    void buildCylinders();
};




