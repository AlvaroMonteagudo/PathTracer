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

    void setMaterial(shared_ptr<Material> material);

    template <class M>
    void setMaterial(M material)
    {
        for (const shared_ptr<Shape> &face : faces)
        {
            face->setMaterial(material);
        }
    }


protected:

    Point a, b, c, d, center, top;

    std::vector<shared_ptr<Shape>> faces;
};