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

#include <vector>
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

    Dir getNormal(const Point &intersectedPoint) const override;

    Plane moveX(float offset) const;

    Plane moveY(float offset) const;

    Plane moveZ(float offset) const;

    template <class S>
    void addHole(const S &shape) {
        holes.push_back(make_shared<S>(shape));
    }

    template <class S>
    void addHole(const shared_ptr<S> &shape) {
        holes.push_back(shape);
    }
	
	vector<Point> getPointLIghts(int samples){
        vector<Point> resul = vector<Point>(2);
        return resul;
    }

    const Point &getPoint() const;

private:

    /// PLANE PARAMETERS
    Dir normal;

    Point point;

    std::vector<shared_ptr<Shape>> holes;
};


#define FLOOR(x) Plane(Dir(0, 1, 0), Point(0, x, 0))
#define CEILING(x) Plane(Dir(0, -1, 0), Point(0, x, 0))
#define LEFT(x) Plane(Dir(1, 0, 0), Point(x, 0, 0))
#define RIGHT(x) Plane(Dir(-1, 0, 0), Point(x, 0, 0))
#define BOTTOM(x) Plane(Dir(0, 0, -1), Point(0, 0, x))
#define BACK(x) Plane(Dir(0, 0, 1), Point(0, 0, X))

