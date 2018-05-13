#pragma once

#include <vector>
#include "Quad.h"

class Box {

public:

    const vector<shared_ptr<Quad>> &getFaces() const;

    Box(const Quad &quad, float height);

    void setMaterial(shared_ptr<Material> material);

    template <class M>
    void setMaterial(M material)
    {
        for (const auto &face : faces)
        {
            face->setMaterial(material);
        }
    }

    Box moveX(float offset) const;

    Box moveY(float offset) const;

    Box moveZ(float offset) const;

    void setHeight(float height);

protected:

    std::vector<shared_ptr<Quad>> faces;

    Quad base;

    float height;

};