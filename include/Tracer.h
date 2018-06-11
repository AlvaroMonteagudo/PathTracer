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
#include "Mat.h"
#include "Image.h"
#include <cstring>
#include <iostream>
#include <random>
#include <thread>

class Tracer {

public:

    /**
     * Constructor for path tracer
     * @param filename where image will be saved
     * @param scene to be renderized and stored in file
     */
    Tracer(string filename, const Scene &scene);

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
    RGB radiance(const Ray &_ray, int depth) const;

    RGB russianRoulette(const Ray &ray, const Shape &shape, const Material &material, const Point &intersectedPoint, const Dir &normal, int depth) const;

    inline bool intersect(const Ray &ray, float &distance, int &id) const;

    RGB directLighting(const Point &intersectedPoint, const Dir &normal,
                       const shared_ptr<Shape> &shape, const Ray &ray) const;

    /// PUBLIC PARAMETERS
    int SAMPLES = 32, MAX_DEPTH = 5;

    bool NEE = false;

private:

    /// TRACER PARAMETERS
    string outfileName;

    Scene scene;

    Camera camera;

    Image image;

    int totalPixels;

    vector<shared_ptr<Shape>> shapes;
};


