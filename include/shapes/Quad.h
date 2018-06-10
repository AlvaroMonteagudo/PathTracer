#pragma once

#include "Plane.h"
#include "Triangle.h"

class Quad : public Plane {

public:

    Quad(const Point &a, const Point &b, const Point &c, const Point &d);

    Quad(const Point &a, const Point &b, const Point &c);

    float intersect(const Ray &ray) const;

    Dir getNormal(const Point &intersectedPoint) const;

    Dir getNormal() const;

    tuple<Point, Point, Point, Point> getCorners() const;

    const Point &getCenter() const;

    Quad moveX(float offset) const;

    Quad moveY(float offset) const;

    Quad moveZ(float offset) const;
	
	vector<Point> sampleLight2(int samples);

    /*void setRefractiveIndex(float refrIndex)
    {
        t1.setRefractiveIndex(refrIndex);
        t2.setRefractiveIndex(refrIndex)
    }*/

protected:

    Point a, b, c, d;
	
	float minX=999999, minY=999999, minZ=999999, maxX=-999999, maxY=-999999, maxZ=-999999;

    Point center;

    Triangle t1, t2;

};
