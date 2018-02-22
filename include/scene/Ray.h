/**
 *  @file    Ray.h
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    12/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Header file for ray class
 *  Ray structure data used for ray trace, based on a point and a direction.
 */

#pragma once

#include "Point.h"

class Ray {

public:

    /**
     * Default constructor
     */
    Ray();

    /**
     * Ray constructor
     * @param source of the ray
     * @param direction of the ray
     */
    Ray(const Point &source, const Dir &direction);

    /**
     * Ray constructor
     * @param source of the ray
     * @param destination point use to set ray direction
     */
    Ray(const Point &source, const Point &destination);

    /// GETTERS
    Point getSource() const;

    Dir getDirection() const;

    Point getPoint(float distance) const;


protected:

    /// RAY PARAMETERS
    Point source;

    Dir direction;
};
