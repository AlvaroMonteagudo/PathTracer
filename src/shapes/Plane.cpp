/**
 *  @file    Plane.cpp
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    12/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Implementation for plane class
 */

#include <limits>
#include "Plane.h"

/**
 * Constructor for plane
 * @param normal of the plane
 * @param point: a point of the plane
 */
Plane::Plane(const Dir &normal, const Point &point) :
            Shape(), normal((normal).normalize()) , point(point) { }

/**
 * Intersection method
 * @param ray: input ray
 * @return distance from ray origin to intersection point if intersects, max float value otherwise
 */
float Plane::intersect(const Ray &ray) const {

    for (auto shape : holes) {
        if (shape->intersect(ray) != MAX_FLOAT) { // Intersects a hole return max float
            return MAX_FLOAT;
        }
    }

    float num = (point - ray.getSource()).dot(normal);
    float den = ray.getDirection().dot(normal);

    // There is an intersection
    if (den != 0){
        float x = num / den;
        return x > THRESHOLD ? x : MAX_FLOAT;
    } else if (num != 0) { // denominator is 0, line parallel to plane
        return MAX_FLOAT;
    } else { // Both are zero, line is in the plane
        return THRESHOLD;
    }
}

/// GETTERS

Dir Plane::getNormal(const Point &intersectedPoint) const {
    return normal;
}

Dir Plane::getNormal() const {
    return normal;
}

Plane Plane::moveX(const float offset) const {
    return { normal, point.moveX(offset) };
}

Plane Plane::moveY(float offset) const {
    return { normal, point.moveY(offset) };
}

Plane Plane::moveZ(float offset) const {
    return { normal, point.moveZ(offset) };
}

const Point &Plane::getPoint() const {
    return point;
}
