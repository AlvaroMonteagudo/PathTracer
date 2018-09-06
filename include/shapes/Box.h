#pragma once

#include <vector>
#include "Quad.h"

class Box {

public:

    const vector<shared_ptr<Quad>> &getFaces() const;

    Box(const Quad &quad, float height);

    void setMaterial(shared_ptr<Material> material);

    template <class M>
    void setMaterial(M material) {
        for (const auto &face : faces) {
            face->setMaterial(material);
        }
    }

    template <class RI>
    void setRefractiveIndex(RI refrIndex) {
        for (const auto &face : faces) {
            face->setRefractiveIndex(refrIndex);
        }
    }

    void setEmit(const RGB &rgb) {
        for (const auto &face : faces) {
            face->setEmit(rgb);
        }
    }

    void setEmit(const RGB &rgb, int face){
        assert(0 <= face <= 5);
        faces.at(face)->setEmit(rgb);
    }

    template <class RI>
    void setRefractiveIndex(RI refrIndex, int face){
        assert(0 <= face <= 5);
        faces.at(face)->setRefractiveIndex(refrIndex);
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