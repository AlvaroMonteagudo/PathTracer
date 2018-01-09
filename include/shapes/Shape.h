/**
 *  @file    Shape.h
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    12/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Header file for shape class
 *  Mother class for every available shape implemented for this ray trace
 *  It declares virtual methods for every sub class that inherits from this class
 *  such as intersection methods o obtaining normal from the shape.
 */

#pragma once

#include "../scene/Ray.h"
#include "../algebraUtils/Point.h"
#include "../scene/RGB.h"
#include <iostream>
#include <limits>

#define THRESHOLD 0.0001
#define MIN_FLOAT std::numeric_limits<float>::min()
#define MAX_FLOAT std::numeric_limits<float>::max()
#define EPSILON   std::numeric_limits<float>::epsilon()

#define AIR_RI 1.000293
#define WATER 1.333
#define GLASS 1.5
#define DIAMOND 2.42
#define VACUUM 1

class Shape {

public:

    /**
     * Intersection method
     * @return distance of intersection
     */
    virtual float intersect(const Ray &ray) const  = 0;

    /**
     * Get normal of the shape
     * @param intersectedPoint where ray intersects shape
     * @return normal of the shape
     */
    virtual Dir getNormal(const Point &intersectedPoint) const = 0;

    /**
     * Inline function, clamp for ray refraction
     * @param lo lower bound
     * @param hi higher bound
     * @param v value itself
     * @return max between lo and min between hi and v
     */
    inline
    float clamp(const float &lo, const float &hi, const float &v)
    {
        return std::max(lo, std::min(hi, v));
    }

    /**
     * Get dir of ray reflected
     * @param rayDir: direction of the ray intersecting shape
     * @param nhit: normal of the shape in the intersection point
     * @return direction of ray reflected in this shape
     */
    Dir getDirRayReflected(const Dir &rayDir, const Dir &nhit) const {
        float product = rayDir.dot(nhit) * 2.0f;
        return rayDir - nhit*product;
    }

    /**
     * Get dir of ray refracted
     * @param rayDir: ray direction that intersects the shape
     * @param normal: normal of the shape in the intersection point
     * @return direction of refracted ray n the intersection point
     * @note Code adapted from website: www.scratchapixel,com
     *       Source: https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
     *       Author: @ 2009-2016 Scratchapixel
     */
    Dir getDirRayRefracted(const Dir &rayDir, const Dir& normal){

        float cosi = clamp(-1, 1, normal.dot(rayDir));

        float refrIndexFrom = 1, refrIndexTo = refractiveIndex ;

        Dir nRefr = normal;

        if (cosi < 0) {
            // We are outside the surface, we want cos(theta) to be positive
            cosi = cosi*-1.0f;
        } else {
            std::swap(refrIndexFrom, refrIndexTo);
            nRefr = normal*-1.0f;
        }

        float eta = refrIndexFrom / refrIndexTo;

        float k = 1 - eta * eta * (1 - cosi * cosi);

        if (k < 0) {
            return getDirRayReflected(rayDir * -1, nRefr);
        }

        return rayDir  * eta + nRefr * (eta * cosi - sqrtf(k));

    }

    /// GETTERS

    const RGB &getKd() const {
        return kd;
    }

    const RGB &getKs() const {
        return ks;
    }

    const RGB &getKr() const {
        return kr;
    }

    const RGB &getKt() const {
        return kt;
    }

    float getShininess() const {
        return shininess;
    }

    /// SETTERS

    void setKd(const RGB &kd) {
        Shape::kd = kd;
    }

    void setKs(const RGB &ks) {
        Shape::ks = ks;
    }

    void setKr(const RGB &kr) {
        Shape::kr = kr;
    }

    void setKt(const RGB &kt) {
        Shape::kt = kt;
    }

    void setShininess(float shininess) {
        Shape::shininess = shininess;
    }

    void setRefractiveIndex(float refractiveIndex) {
        Shape::refractiveIndex = refractiveIndex;
    }

    void setFeatures(const RGB &kd, const RGB &ks, const RGB &kr, const RGB & kt){
        this->kd = kd;
        this->ks = ks;
        this->kr = kr;
        this->kt = kt;
    }

private:

    /// Shape features coefficients
    RGB kd, ks, kr , kt;

    /// Other shape values
    float shininess = 0.0f, refractiveIndex = AIR_RI;

};
