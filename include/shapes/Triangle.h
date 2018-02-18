#pragma once

#include "Plane.h"

class Triangle : public Plane {
public:

    Triangle(const Point &a, const Point &b, const Point &c);

    float intersect(const Ray &ray) const;

    const Point &getA() const;

    const Point &getB() const;

    const Point &getC() const;

protected:

    Point a, b, c;

    /** Cached values to make a triangle intersection faster. */
    Dir v0, v1;
    float d00, d01, d11, denominator;
};
