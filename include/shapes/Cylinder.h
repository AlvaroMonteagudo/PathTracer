#pragma once

#include "Shape.h"

class Cylinder : public Shape {

public:

    Cylinder();

    Cylinder(const Point &_point, const Dir &_axis, float _radius);

    float intersect(const Ray &ray) const;

    Dir getNormal(const Point &intersectedPoint) const;

private:

    //Circle base, top;

    Point point;

    Dir axis;

    float radius, sqrd_radius;

};

