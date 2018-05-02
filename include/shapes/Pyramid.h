#pragma once

#include <vector>
#include "Quad.h"

class Pyramid {

public:

    Pyramid(const Quad &quad, float height);

    Pyramid(const Quad &quad, const Point &top);

    Pyramid(const Triangle &triangle, float height);

    Pyramid(const Triangle &triangle, const Point &top);

    void setMaterial(shared_ptr<Material> material);

    template <class M>
    void setMaterial(M material)
    {
        for (const shared_ptr<Shape> &face : faces)
        {
            face->setMaterial(material);
        }
    }

    const vector<shared_ptr<Shape>> &getFaces() const;


protected:

    Point a, b, c, d, center, top;

    std::vector<shared_ptr<Shape>> faces;
};