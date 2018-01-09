#pragma once

#include "Plane.h"

class Triangle : public Plane {
public:

    Triangle(const Point &a, const Point &b, const Point &c);

    const Point &getA() const;

    const Point &getB() const;

    const Point &getC() const;

public:

private:

    Point a, b, c;
};
