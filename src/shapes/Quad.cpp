#include <tuple>
#include "Quad.h"

Quad::Quad(const Point &a, const Point &b, const Point &c, const Point &d)
    : Plane((b - a).cross(c - a).normalize(), a),
      a(a), b(b), c(c), d(d),
      t1(Triangle(a, b, c)),
      t2(Triangle(a, c, d)) { }

Quad::Quad(const Point &a, const Point &b, const Point &c)
    : Plane((b - a).cross(c - a).normalize(), a),
      a(a), b(b), c(c), half_bc(b.getMiddlePointWith(c)), d(a.getTwiceDistanceWith(half_bc)),
      t1(Triangle(a, b, c)), t2(Triangle(b, c, d))   {
}


float Quad::intersect(const Ray &ray) const {
    float dist = Plane::intersect(ray);
    if (dist == MAX_FLOAT) return MAX_FLOAT;

    return (t1.intersect(ray) < MAX_FLOAT) ? dist : (t2.intersect(ray) < MAX_FLOAT) ? dist : MAX_FLOAT;
}

tuple<Point, Point, Point, Point> Quad::getCorners() const {
    return make_tuple(a, b, c, d);
}

Dir Quad::getNormal(const Point &intersectedPoint) const {
    return Plane::getNormal(intersectedPoint);
}

Dir Quad::getNormal() const {
    return Plane::getNormal();
}

