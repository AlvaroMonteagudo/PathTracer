#pragma once

#include <vector>
#include "Quad.h"

class Pyramid3 {

public:

    Pyramid3(const Triangle &triangle, float height);

    Pyramid3(const Triangle &triangle, const Point &top);

    void setMaterial(shared_ptr<Material> material);

    template <class M>
    void setMaterial(M material)
    {
        for (const shared_ptr<Shape> &face : faces)
        {
            face->setMaterial(material);
        }
    }

    template <class RI>
    void setRefractiveIndex(RI refrIndex)
    {
        for (const auto &face : faces)
        {
            face->setRefractiveIndex(refrIndex);
        }
    }

    void setEmit(RGB &rgb,int samples)
    {
        for (const auto &face : faces)
        {
            face->setEmit(rgb,samples);
        }
    }

    const vector<shared_ptr<Shape>> &getFaces() const;

    Pyramid3 moveX(float offset) const;

    Pyramid3 moveY(float offset) const;

    Pyramid3 moveZ(float offset) const;

    void setHeight(float height);


protected:

    Point a, b, c, center, top;

    std::vector<shared_ptr<Shape>> faces;

    Triangle base;

    float height = 0.0f;
};
