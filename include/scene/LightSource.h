/**
 *  @file    LightSource.h
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    16/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Header file for light source class
 *  Artificial light needed to enlight the scene to be rendered.
 *  A scene can contain multiple instances of light.
 */

#pragma once

#include "Point.h"

class LightSource {

public:

    /**
     * Default constructor
     */
    LightSource();

    /**
     * Light source constructor
     * @param point where light is placed
     * @param intensity of the light source
     */
    LightSource(const Point &point, float intensity);

    /// GETTERS
    const Point &getPoint() const;

    float getIntensity() const;

    /// SETTERS
    void setPoint(const Point &point);

    void setIntensity(float intensity);


private:

    /// LIGHTSOURCE PARAMETERS
    Point point;

    float intensity;

};