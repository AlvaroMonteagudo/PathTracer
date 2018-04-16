/**
 *  @file    Plane.h
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    12/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Header file for plane class
 *  Plane definition with point and normal, infinite shape.
 *
 */

#pragma once

#include "Dir.h"
#include "Shape.h"
#include "Point.h"
#include "Ray.h"

class Plane : public Shape {

public:

    /**
     * Constructor for plane
     * @param normal of the plane
     * @param point: a point of the plane
     */
    Plane(const Dir &normal, const Point &point);

    /**
     * Intersection method
     * @param ray: input ray
     * @return distance from ray origin to intersection point if intersects, max float value otherwise
     */
    float intersect(const Ray &ray) const;

    /// GETTERS
    Dir getNormal() const;

    Dir getNormal(const Point &intersectedPoint) const;

private:

    /// PLANE PARAMETERS
    Dir normal;

    Point point;
};
