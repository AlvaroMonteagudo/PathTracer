#pragma once

#include "Quad.h"

class Box : public Shape {

public:

    Box(const Quad &quad, const float depth);

    float intersect(const Ray &ray) const;

    Dir getNormal(const Point &intersectedPoint) const;

    void setMaterial(shared_ptr<Material> material);

    template <class M>
    void setMaterial(M material)
    {
        for (const shared_ptr<Quad> &face : faces)
        {
            face->setMaterial(material);
        }
    }

protected:

    shared_ptr<Quad> faces[6];

private:

    shared_ptr<Quad> faceHitted;

};