#pragma once

#include "Plane.h"
#include "Triangle.h"

class Quad : public Plane {

public:

    Quad(const Point &a, const Point &b, const Point &c, const Point &d);

    float intersect(const Ray &ray) const;

    Dir getNormal(const Point &intersectedPoint) const;

    Dir getNormal() const;

    tuple<Point, Point, Point, Point> getCorners() const;

protected:

    Point v00, v10, v11, v01;

    Point center;

    Triangle t1, t2;

};
