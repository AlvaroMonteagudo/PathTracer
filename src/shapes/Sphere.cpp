/**
 *  @file    Sphere.cpp
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    12/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Implementation for sphere class
 */

#include <iostream>
#include "Sphere.h"

/**
 * Default constructor
 */

Sphere::Sphere() = default;

/**
 * Sphere constructor
 * @param radius of the sphere
 * @param center of the sphere
 */
Sphere::Sphere(float radius, const Point &center) :
        Shape(), radius(radius), center(center), sqrd_radius(radius*radius) { }

/**
 * Intersection method
 * @param ray: input ray
 * @return distance from ray origin to intersection point if intersects, max float value otherwise
 */
float Sphere::intersect(const Ray &ray) const {
    Dir d = ray.getSource() - center;

    float a = 1.0f;
    float b = 2.0f * ray.getDirection().dot(d);
    float c = d.dot(d) - sqrd_radius;
    float discriminant = b*b - 4*a*c;

    // Abort if less than 0
    if (discriminant < 0.0) {
        return MAX_FLOAT;
    } else if (discriminant > 0.0) {
        float x1 = (-b - sqrt(discriminant)) / (2.0f * a);
        float x2 = (-b + sqrt(discriminant)) / (2.0f * a);

        if ((x1 > THRESHOLD) && ((x1 < x2) || (x2 <= THRESHOLD))) {
            return x1;
        } else if ((x2 > THRESHOLD) && ((x2 < x1) || (x1 <= THRESHOLD))) {
            return x2;
        } else {
            return MAX_FLOAT;
        }
    } else {
        float x = -b / (2.0f * a);
        return x > THRESHOLD ? x : MAX_FLOAT;
    }
}

/**
 * Get normal of the sphere at a point
 * @param intersectedPoint: point to get normal from
 * @return normal between itnersected point and sphere center
 */
Dir Sphere::getNormal(const Point &intersectedPoint) const {
    return (center - intersectedPoint).normalize(); //  DIV radius;
}

Sphere Sphere::moveX(const float offset) const {
    return { radius, center.moveX(offset) };
}

Sphere Sphere::moveY(float offset) const {
    return { radius, center.moveY(offset) };
}

Sphere Sphere::moveZ(float offset) const {
    return { radius, center.moveZ(offset) };
}




