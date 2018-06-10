#pragma once

#include "Shape.h"

class Cylinder : public Shape {

public:

    Cylinder();

    Cylinder(const Point &_point, const Dir &_axis, float _radius);

    float intersect(const Ray &ray) const;

    Dir getNormal(const Point &intersectedPoint) const;
	
	vector<Point> sampleLight2(int samples){
        vector<Point> resul = vector<Point>(2);
        return resul;
    }

private:

    //Circle base, top;

    Point point;

    Dir axis;

    float radius, sqrd_radius;

};

