#pragma once

#include <vector>
#include "Quad.h"

class Pyramid3 {

public:

    Pyramid3(const Triangle &triangle, float height);

    Pyramid3(const Triangle &triangle, const Point &top);

    void setMaterial(shared_ptr<Material> material);

    template <class M>
    void setMaterial(M material) {
        for (const shared_ptr<Shape> &face : faces) {
            face->setMaterial(material);
        }
    }

    template <class RI>
    void setRefractiveIndex(RI refrIndex) {
        for (const auto &face : faces) {
            face->setRefractiveIndex(refrIndex);
        }
    }

    void setEmit(RGB &rgb) {
        for (const auto &face : faces) {
            face->setEmit(rgb);
        }
    }

    void setEmit(const RGB &rgb, int face){
        assert(0 <= face < 4);
        faces.at(face)->setEmit(rgb);
    }

    template <class RI>
    void setRefractiveIndex(RI refrIndex, int face){
        assert(0 <= face < 4);
        faces.at(face)->setRefractiveIndex(refrIndex);
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
