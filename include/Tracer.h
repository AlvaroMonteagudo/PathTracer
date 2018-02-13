/**
 *  @file    Tracer.h
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    16/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Header for tracer class
 */

#include <cmath>
#include "scene/Scene.h"
#include <vector>
#include <fstream>
#include "algebraUtils/Mat.h"
#include "scene/Image.h"
#include <cstring>
#include <iostream>
#include <random>
#include <thread>

class Tracer {

public:

    /**
     * Constructor for path tracer
     * @param filename where mage will be saved
     */
    explicit Tracer(string filename);

    /**
     * Constructor for path tracer
     * @param filename where mage will be saved
     * @param scene to be renderized and stored in file
     */
    explicit Tracer(string filename, const Scene &scene);

    /**
     * Render image method
     */
    void renderImage() const;

    /**
     * Render image method using multithreading
     */
    void renderImageMultithread() const;

    /**
     * Render range of image
     * @param start line of image to be rendered
     * @param end line of image to be rendered
     */
    void renderImageLines(int start, int end);

    /**
     * Ray trace main method
     * @param ray emitted
     * @param depth limit for the ray
     * @param indirectSteps: number of bounces for indirect light
     * @return color obtained of the path this ray follows
     */
    RGB radiance(const Ray ray, int depth) const;

    /**
     * Direct light method
     * @param intersectedPoint: point of the shape
     * @param normalShape: shape normal
     * @param lights: lights of the scene
     * @param shape: shape intersected
     * @param ray: ray intersecting the shape
     * @return direct light color
     */
    RGB directLight(const Point &intersectedPoint, const Dir &normalShape,
                    const shared_ptr<Shape> &shape, const Ray &ray) const;

    /**
     * Indirect light method
     * @param intersectedPoint: point of the shape
     * @param normalShape: shape normal
     * @param shape: shape intersected
     * @param ray: ray intersecting the shape
     * @param depth: depth of path
     * @param indirectSteps: number of indirect steps
     * @return indirect light color
     */
    RGB indirectLight(const Point &intersectedPoint, const Dir &normalShape, shared_ptr<Shape> &shape,
                      const Ray &ray, int depth) const;

    /**
     * Specular light method
     * @param intersectedPoint: point of the shape
     * @param normalShape: shape normal
     * @param shape: shape intersected
     * @param ray: ray intersecting the shape
     * @param depth: depth of path
     * @param indirectSteps: number of indirect steps
     * @return specular light color
     */
    RGB deltaInteraction(const Point &intersectedPoint, const Dir &normalShape,
                         const shared_ptr<Shape> &shape, const Ray &ray, int depth, int indrectSteps) const;

    /**
     * Phong's BRDF method
     * @param ray
     * @param light
     * @param normal of the shape
     * @param shape intersected
     * @param point where shape was intersected
     * @return color from Phong's BRDF formula
     */
    RGB Phong(const Ray &ray, const Ray &light, const Dir &normal, shared_ptr<Shape> shape,
              const Point &point) const;

    RGB RussianRoulette(const Point &intersectedPoint, const shared_ptr<Shape> shape, int depth) const;

    inline bool intersect(const Ray &ray, float &distance, int &id) const;

    /// PUBLIC PARAMETERS
    int MAX_DEPTH = 5, MAX_INDIRECT_STEPS = 1, SAMPLES = 128;

private:

    /// TRACER PARAMETERS
    string outfileName;

    Scene scene;

    Camera camera;

    Image image;

    int totalPixels;

    vector<shared_ptr<Shape>> shapes;

    vector<LightSource> lights;

    vector<AreaLight> areaLights;
};


