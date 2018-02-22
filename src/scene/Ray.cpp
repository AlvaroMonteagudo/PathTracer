/**
 *  @file    Ray.cpp
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    12/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Implementation for light source class
 */

#include "Ray.h"

/**
 * Default constructor
 */
Ray::Ray() = default;

/**
 * Ray constructor
 * @param source of the ray
 * @param direction of the ray
 */
Ray::Ray(const Point &source, const Dir &direction) :
        source(source), direction(direction.normalize()) {}

/**
 * Ray constructor
 * @param source of the ray
 * @param destination point use to set ray direction
 */
Ray::Ray(const Point &source, const Point &destination) :
        source(source), direction((destination - source).normalize()){}

/// GETTERS

Point Ray::getSource() const {
    return source;
}

Dir Ray::getDirection() const  {
    return direction;
}

Point Ray::getPoint(float distance) const {
    return source + direction * distance;
}



