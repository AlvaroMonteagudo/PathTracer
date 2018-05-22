#pragma once


#include "Circle.h"

class Cylinder : public Shape {

public:

    Cylinder(Circle &base, float height);

    float intersect(const Ray &ray) const;

    Dir getNormal(Point &intersectedPoint);

private:

    Circle base, top;

    float height;

};

