#pragma once

#include "Circle.h"

class Cone : public Shape {

public:

    Cone(const Circle &base, float height);

    float intersect(const Ray &ray) const;

    Dir getNormal(const Point &intersectedPoint) const;

    void setMaterial(const RGB &kd, const RGB &ks, const RGB &kr, const RGB & kt);

protected:

    shared_ptr<Circle> base;

    Point center, top;

    float radius, angle;

    Dir V;

};
