#pragma once

#include "Plane.h"

class Circle : public Plane {

public:

    Circle(const Point &p, const Dir &normal, float radius);

    float intersect(const Ray &ray) const;

    const Point &getPoint() const;

    float getRadius() const;

protected:

    Point point;

    float radius;
};
