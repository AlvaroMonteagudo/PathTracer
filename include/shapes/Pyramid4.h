#pragma once

#include <vector>
#include "Quad.h"

class Pyramid4 {

public:

    Pyramid4(const Quad &quad, float height);

    Pyramid4(const Quad &quad, const Point &top);

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

    void setEmit(RGB &rgb, int samples)
    {
        for (const auto &face : faces)
        {
            face->setEmit(rgb,samples);
        }
    }

    const vector<shared_ptr<Shape>> &getFaces() const;

    Pyramid4 moveX(float offset) const;

    Pyramid4 moveY(float offset) const;

    Pyramid4 moveZ(float offset) const;

    void setHeight(float height);


protected:

    Point a, b, c, d, center, top;

    std::vector<shared_ptr<Shape>> faces;

    Quad base;

    float height = 0.0f;
};