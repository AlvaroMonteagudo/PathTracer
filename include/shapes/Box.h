#pragma once

#include <vector>
#include "Quad.h"

class Box : public Shape {

public:
    const vector<shared_ptr<Quad>> &getFaces() const;

    Box(const Quad &quad, const float depth);

    float intersect(const Ray &ray) const;

    Dir getNormal(const Point &intersectedPoint) const;

    void setMaterial(shared_ptr<Material> material);

    template <class M>
    void setMaterial(M material)
    {
        for (const auto &face : faces)
        {
            face->setMaterial(material);
        }
    }

protected:

    std::vector<shared_ptr<Quad>> faces;

};