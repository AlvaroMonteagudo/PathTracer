#pragma once

#include <vector>
#include "Quad.h"

class Pyramid : public Shape {

public:

    Pyramid(const Quad &quad, float height);

    Pyramid(const Quad &quad, const Point &top);

    Pyramid(const Triangle &triangle, float height);

    Pyramid(const Triangle &triangle, const Point &top);

    float intersect(const Ray &ray) const;

    Dir getNormal(const Point &intersectedPoint) const;

    void setMaterial(const RGB &kd, const RGB &ks, const RGB &kr, const RGB & kt);


protected:

    Point a, b, c, d, center, top;

    std::vector<shared_ptr<Shape>> faces;
};