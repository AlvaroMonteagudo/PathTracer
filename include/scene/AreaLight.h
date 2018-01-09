#pragma once

#include "../algebraUtils/Point.h"
#include "../shapes/Plane.h"

class AreaLight  : public Plane{

public:

    AreaLight(const Point &upCorner, const Point &downCorner, const Dir &normal, const Dir &xDir, const Dir &yDir, float intensity);

    float intersect(const Ray &ray) const;

private:

    Point upCorner, downCorner;

    Point minValues, maxValues;

    float intensity;

};