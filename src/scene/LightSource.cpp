/**
 *  @file    LightSource.cpp
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    16/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Implementation for light source class
 */

#include "LightSource.h"

/**
 * Default constructor
 */
LightSource::LightSource() = default;

/**
 * Light source constructor
 * @param point where light is placed
 * @param intensity of the light source
 */
LightSource::LightSource(const Point &point, float intensity) :
        point(point), intensity(intensity) {}

/// GETTERS

const Point &LightSource::getPoint() const {
    return point;
}

float LightSource::getIntensity() const {
    return intensity;
}

/// SETTERS

void LightSource::setPoint(const Point &point) {
    LightSource::point = point;
}

void LightSource::setIntensity(float intensity) {
    LightSource::intensity = intensity;
}
