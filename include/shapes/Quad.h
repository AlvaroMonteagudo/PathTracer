#pragma once

#include "Plane.h"
#include "Triangle.h"

class Quad : public Plane {

public:

    Quad(const Point &a, const Point &b, const Point &c, const Point &d);

    Quad(const Point &a, const Point &b, const Point &c);

    float intersect(const Ray &ray) const;

    Dir getNormal(const Point &intersectedPoint) const;

    Dir getNormal() const;

    tuple<Point, Point, Point, Point> getCorners() const;

protected:

    Point a, b, c, d;

    Point center;

    Point half_bc;

    Triangle t1, t2;

};
