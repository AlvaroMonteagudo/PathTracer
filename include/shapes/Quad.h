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

    void setEmit(const RGB &_emit, int samples = 0) {
    	setSampleLights(samples);
    	Shape::setEmit(_emit);
    }

    void setSampleLights(int samples);
	
	vector<Point> getPointLights();

    /*void setRefractiveIndex(float refrIndex)
    {
        t1.setRefractiveIndex(refrIndex);
        t2.setRefractiveIndex(refrIndex)
    }*/

protected:

    Point a, b, c, d;

    Point center;

    Triangle t1, t2;

    std::vector<Point> sampledLights;

};
