#pragma once

#include "Quad.h"

class Box : public Shape {

public:

    Box(const Quad &quad, const float depth);

    float intersect(const Ray &ray) const;

    Dir getNormal(const Point &intersectedPoint) const;

    void setMaterial(const RGB &kd, const RGB &ks, const RGB &kr, const RGB & kt);

protected:

    shared_ptr<Quad> faces[6];

private:

    shared_ptr<Quad> faceHitted = nullptr;

};