#pragma once

#include "Plane.h"

class Triangle : public Plane {

public:

    Triangle(const Point &a, const Point &b, const Point &c);

    float intersect(const Ray &ray) const;

    tuple<Point, Point, Point> getCorners() const;

    const Point &getCenter() const;

    Triangle moveX(float offset) const;

    Triangle moveY(float offset) const;

    Triangle moveZ(float offset) const;
	
	vector<Point> getPointLIghts(int samples){
        vector<Point> resul = vector<Point>(2);
        return resul;
    }

protected:

    Point a, b, c, center;

    /** Cached values to make a triangle intersection faster. */
    Dir v0, v1;
    float d00, d01, d11, denominator;

};
