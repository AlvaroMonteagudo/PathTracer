//
// Created by alvaro on 31/05/18.
//

#include <Point.h>
#include <Triangle.h>
#include <MeshTriangle.h>

MeshTriangle::MeshTriangle(const Point &a, const Point &b, const Point &c,
                           const Dir &_normalA, const Dir &_normalB,const Dir &_normalC) :
        Triangle(a, b, c),
        normalA(_normalA),
        normalB(_normalB),
        normalC(_normalC) {}

Dir MeshTriangle::getNormal(const Point &intersectedPoint) const {
    Dir v2 = intersectedPoint - a;
    float d20 = v2.dot(v0);
    float d21 = v2.dot(v1);
    // Barycentric coordinates.
    float alpha = (d11 * d20 - d01 * d21) / denominator;
    float beta = (d00 * d21 - d01 * d20) / denominator;
    float gamma = 1.0f - alpha - beta;
    // Normal interpolation.
    return normalA * gamma + normalB * alpha + normalC * beta;
}
