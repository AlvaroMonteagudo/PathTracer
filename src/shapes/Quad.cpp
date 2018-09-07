#include <tuple>
#include "Quad.h"


Quad::Quad(const Point &a, const Point &b, const Point &c, const Point &d)
    : Plane((b - a).cross(c - a).normalize(), a),
      a(a), b(b), c(c), d(d),
      t1(Triangle(a, b, c)),
      t2(Triangle(b, c, d)) {

    center = (a + b + c + d) / 4.0f;
}

Quad::Quad(const Point &a, const Point &b, const Point &c)
    : Plane((b - a).cross(c - a).normalize(), a),
      a(a), b(b), c(c), d(a.getTwiceDistanceWith(b.getMiddlePointWith(c))),
      t1(Triangle(a, b, c)), t2(Triangle(b, c, d)),
      center(b.getMiddlePointWith(c))  { }


float Quad::intersect(const Ray &ray) const {
    float dist = Plane::intersect(ray);
    if (dist == MAX_FLOAT) return MAX_FLOAT;

    return (t1.intersect(ray) < MAX_FLOAT) ? dist : (t2.intersect(ray) < MAX_FLOAT) ? dist : MAX_FLOAT;
}

tuple<Point, Point, Point, Point> Quad::getCorners() const {
    return make_tuple(a, b, c, d);
}

Dir Quad::getNormal(const Point &intersectedPoint) const {
    return t1.getNormal(intersectedPoint);
}

Dir Quad::getNormal() const {
    return t1.getNormal();
}

const Point &Quad::getCenter() const {
    return center;
}

Quad Quad::moveX(float offset) const {
    return { a.moveX(offset), b.moveX(offset), c.moveX(offset), d.moveX(offset) };
}

Quad Quad::moveY(float offset) const {
    return { a.moveY(offset), b.moveY(offset), c.moveY(offset), d.moveY(offset) };
}

Quad Quad::moveZ(float offset) const {
    return { a.moveZ(offset), b.moveZ(offset), c.moveZ(offset), d.moveZ(offset) };
}


vector<Point> Quad::getPointLights(){
    return sampledLights;
}

void Quad::setSampleLights(int samples) {

    srand(static_cast<unsigned int>(time(nullptr)));
    sampledLights = vector<Point>();

    if (samples == 1){
        sampledLights.push_back(center);
        return;
    }

    Point borderA = a.getMiddlePointWith(center);
    Point borderB = b.getMiddlePointWith(center);
    Point borderC = c.getMiddlePointWith(center);

    for(int i=0;i<samples;i++) {
        float rand1 = ((float) rand() / (RAND_MAX));
        float rand2 = ((float) rand() / (RAND_MAX));
        Dir dir1 = borderB - borderA;
        Dir dir2 = borderC - borderA;
        sampledLights.push_back(borderA + (dir1 * rand1) + (dir2 * rand2));
    }
}

