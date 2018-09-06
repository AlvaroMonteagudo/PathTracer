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

#include "Ray.h"
#include "Point.h"
#include "Camera.h"
#include <iostream>
#include <memory>
#include "mathUtils.h"
#include <vector>
#include <Material.h>

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
     * Get dir of ray reflected
     * @param rayDir: direction of the ray intersecting shape
     * @param nhit: normal of the shape in the intersection point
     * @return direction of ray reflected in this shape
     */
    static Dir getDirRayReflected(const Dir &rayDir, const Dir &nhit) {
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
    Dir getDirRayRefracted(const Dir &rayDir, const Point &point, const Dir& normal) const {

        float eta;
        if (normal == getNormal(point))
            eta = refractiveIndex;
        else eta = 1 / refractiveIndex;

        float cosi = normal.changeDirection().dot(rayDir);

        float k = 1 - eta * eta * (1 - cosi * cosi);

        if (k < 0) {
            return getDirRayReflected(rayDir * -1, normal);
        }
        return rayDir  * eta + normal * (eta * cosi - sqrtf(k));

    }

    /// GETTERS

    shared_ptr<Material> getMaterial() const {
        return material;
    }

    const RGB &getEmit() const {
        return emit;
    }


    void setRefractiveIndex(float refractiveIndex) {
        Shape::refractiveIndex = refractiveIndex;
    }

    void setEmit(const RGB &_emit) {
        emit = _emit;
    }

    void setIntensity(float inte){
        intensity = inte;
    }

    float getIntensity(){
        return  intensity;
    }

    virtual void setMaterial(const shared_ptr<Material> m){
        material = m;
    }

    std::vector<Point> getPointLights() {
        return std::vector<Point>();
    }

    template <class M>
    void setMaterial(const M m) {
        material = make_shared<M>(m);
    }


private:

    /// Shape features coefficients
    shared_ptr<Material> material = LAMBERTIAN;

    RGB emit = BLACK;

    float intensity = 1.0f;

    float refractiveIndex = AIR_RI;

};
