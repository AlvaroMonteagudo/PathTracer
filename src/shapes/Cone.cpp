
#include "Cone.h"
#include <cmath>

/*Cone::Cone(const Circle &base, float height) :
    base(make_shared<Circle>(base)),
    radius(base.getRadius()),
    center(base.getPoint()),
    top(center + base.getNormal() * height),
    V(base.getNormal() * -1),
    angle(atan(radius / height)) // en radianes
{

}*/

Cone::Cone(const Dir &_axis, const Point &_point, float _angle) :
        Shape(), axis(_axis), angle(_angle), point(_point) {
    cos2 = cos(angle) * cos(angle);
    sin2 = sin(angle) * sin(angle);
}

float Cone::intersect(const Ray &ray) const {
    float dotVyVa = ray.getDirection().dot(axis);
    Dir A = ray.getDirection() - axis * (dotVyVa);
    Dir dP = ray.getSource() - point;
    float dotDpVa = dP.dot(axis);
    Dir B = dP - axis * dotDpVa;

    float a = A.dot(A) * cos2 - (dotVyVa * dotVyVa) * sin2;
    float b = 2 * cos2 * A.dot(B) - 2 * sin2 * dotVyVa * dotDpVa;
    float c = cos2 * B.dot(B) - sin2 * dotDpVa * dotDpVa;

    return solveQuadratic(a, b, c);
}

/*float Cone::intersect(const Ray &ray) const {

    float tbase = base->intersect(ray);

    float DdotV = ray.getDirection().dot(V);
    Dir CO = ray.getSource() - top;
    float COdotV = CO.dot(V);
    float DdotCO = ray.getDirection().dot(CO);
    auto cos2 = static_cast<float>(pow(cos(angle), 2));

    auto a = static_cast<float>(pow(DdotV , 2) - cos2);
    float b = 2 * (DdotV * COdotV - DdotCO * cos2);
    auto c = static_cast<float>(pow(COdotV, 2) - CO.dot(CO) * cos2);

    float discriminant = b*b - 4*a*c;

    Point P{};
    float t;

    if (discriminant < 0.0) {
        return MAX_FLOAT;
    } else if (discriminant > 0.0) {
        float x1 = (-b - sqrt(discriminant)) / (2.0f * a);
        float x2 = (-b + sqrt(discriminant)) / (2.0f * a);

        if ((x1 < x2) | (x2 <= THRESHOLD)) {
            t = x1;
            if (x1 < THRESHOLD)  return MAX_FLOAT;
        } else if ((x2 < x1) | (x1 <= THRESHOLD)) {
            t = x2;
            if (x2 < THRESHOLD)  return MAX_FLOAT;
        } else {
            return MAX_FLOAT;
        }
    } else {
        float x = -b / (2.0f * a);
        t = x;
        if (x < THRESHOLD)  return MAX_FLOAT;
    }

    P = ray.getSource() + ray.getDirection() * t;

    if (angle < PI / 2 && (P - top).dot(V) > 0) return tbase > t ? tbase : t;
    else return MAX_FLOAT;
}*/

/*void Cone::setMaterial(const RGB &kd, const RGB &ks, const RGB &kr, const RGB &kt) {
    base->setMaterial(kd, ks, kr, kt);
}*/

Dir Cone::getNormal(const Point &intersectedPoint) const {
    return {1, 0, 0};
}

