/**
 *  @file    Sphere.h
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    12/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Header file for sphere class
 *  Sphere definition with radius and point
 */

#pragma once

#include "Shape.h"

class Sphere : public Shape {

public:

    /**
     * Default constructor
     */
    Sphere();

    /**
     * Sphere constructor
     * @param radius of the sphere
     * @param center of the sphere
     */
    Sphere(float radius, const Point &center);

    /**
     * Intersection method
     * @param ray: input ray
     * @return distance from ray origin to intersection point if intersects, max float value otherwise
     */
    float intersect(const Ray &ray) const;

    /**
     * Get normal of the sphere at a point
     * @param intersectedPoint: point to get normal from
     * @return normal between itnersected point and sphere center
     */
    Dir getNormal(const Point &intersectedPoint) const;

    Sphere moveX(float offset) const;

    Sphere moveY(float offset) const;

    Sphere moveZ(float offset) const;

    void setRadius(float radius);

private:

    /// SPHERE PARAMETERS
    float radius, sqrd_radius;

    Point center;

};