//
// Created by alvaro on 28/12/17.
//

#include "../../include/algebraUtils/Point.h"
#include "../../include/shapes/Triangle.h"

const Point &Triangle::getA() const {
    return a;
}

const Point &Triangle::getB() const {
    return b;
}

const Point &Triangle::getC() const {
    return c;
}

Triangle::Triangle(const Point &a, const Point &b, const Point &c) :
        Plane((b - a).cross(c - a).normalize(), a),
        a(a), b(b), c(c) {}
