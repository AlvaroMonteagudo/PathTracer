#pragma once

#include "Circle.h"

class Cone : public Shape {

public:

    Cone(const Dir &axis, const Point &point, float angle);

    float intersect(const Ray &ray) const;

    Dir getNormal(const Point &intersectedPoint) const;
	
   vector<Point> getPointLIghts(int samples){
        vector<Point> resul = vector<Point>(2);
        return resul;
    }

protected:

    shared_ptr<Circle> base;

    Point center, top, point;

    float radius, angle, cos2, sin2;

    Dir axis;

};
