#include <tuple>
#include "Quad.h"

Quad::Quad(const Point &a, const Point &b, const Point &c, const Point &d)
    : Plane((b - a).cross(c - a).normalize(), a),
      v00(a), v10(b), v11(c), v01(d),
      t1(Triangle(a, b, c)),
      t2(Triangle(a, c, d)) { }

float Quad::intersect(const Ray &ray) const {
    float dist = Plane::intersect(ray);
    if (dist == MAX_FLOAT) return MAX_FLOAT;

    /*Dir E01 = v10 - v00;
    Dir E03 = v01 - v00;
    Dir P = ray.getDirection().cross(E03);
    float det = E03.dot(P);

    Dir T = ray.getSource() - v00;

    float alpha = T.dot(P) / det;

    if (alpha < 0 | alpha > 1) return MAX_FLOAT;

    Dir Q = T.cross(E01);
    float beta = (ray.getDirection().dot(Q)) / det;

    // Reject rays using the barycentric coordinates of
    // the intersecntion point with respect to T'
    if (( alpha + beta ) > 1) {
        Dir E23 = v01 - v11;
        Dir E21 = v10 - v11;
        Dir P2 = ray.getDirection().cross(E21);
        float det2 = E23.dot(P2);

        Dir T2 = ray.getSource() - v11;
        float alpha2 = T2.dot(P2) / det2;

        if (alpha2 < 0) return MAX_FLOAT;

        Dir Q2 = T2.cross(E23);
        float beta2 = ray.getDirection().dot(Q2) / det2;

        if (beta2 < 0) return MAX_FLOAT;
    }

    // Compute the ray parameter of the intersection point
    float t = E03.dot(Q) / det;

    if (t < 0) return MAX_FLOAT;

    return dist;

    Dir E02 = v11 - v00;
    Dir N = E01.cross(E03);*/

    return (t1.intersect(ray) < MAX_FLOAT) ? dist : (t2.intersect(ray) < MAX_FLOAT) ? dist : MAX_FLOAT;
}

tuple<Point, Point, Point, Point> Quad::getCorners() const {
    return make_tuple(v00, v10, v11, v01);
}

Dir Quad::getNormal(const Point &intersectedPoint) const {
    return Plane::getNormal(intersectedPoint);
}

Dir Quad::getNormal() const {
    return Plane::getNormal();
}
