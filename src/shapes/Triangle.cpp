#include "Point.h"
#include "Triangle.h"

Triangle::Triangle(const Point &a, const Point &b, const Point &c) :
        Plane((b - a).cross(c - a).normalize(), a),
        a(a), b(b), c(c),
        v0(b - a),
        v1(c - a),
        d00(v0.dot(v0)),
        d01(v0.dot(v1)),
        d11(v1.dot(v1)),
        denominator(d00 * d11 - d01 * d01),
        center((a + b + c) / 3.0)
{}

tuple<Point, Point, Point> Triangle::getCorners() const {
    return make_tuple(a, b, c);
}

float Triangle::intersect(const Ray &ray) const {
    // Intersection of the ray of light with the plane.
    float t = Plane::intersect(ray);
    if (t == MAX_FLOAT) return MAX_FLOAT;
    Point intersection = ray.getSource() + ray.getDirection() * t;
    // Based in Christer Ericson's Real-Time Collision Detection.
    /* Get the barycentric coordinates for the intersection
     * point with respect to the triangle. */
    Dir v2 = intersection - a;
    float d20 = v2.dot(v0);
    float d21 = v2.dot(v1);
    // Barycentric coordinates.
    float alpha = (d11 * d20 - d01 * d21) / denominator;
    float beta = (d00 * d21 - d01 * d20) / denominator;
    // Gamma is not necessary: float gamma = 1.0f - alpha - beta;
    // Check if the intersection point is inside the triangle bounds.
    return ((alpha >= 0) & (beta >= 0) & (alpha + beta < 1)) ? t : MAX_FLOAT;
}

const Point &Triangle::getCenter() const {
    return center;
}

Triangle Triangle::moveX(float offset) const {
    return { a.moveX(offset), b.moveX(offset), c.moveX(offset) };
}

Triangle Triangle::moveY(float offset) const {
    return { a.moveY(offset), b.moveY(offset), c.moveY(offset) };
}

Triangle Triangle::moveZ(float offset) const {
    return { a.moveZ(offset), b.moveZ(offset), c.moveZ(offset) };
}

