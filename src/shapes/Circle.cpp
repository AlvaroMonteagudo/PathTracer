#include "../../include/shapes/Circle.h"

Circle::Circle(const Point &p, const Dir &normal, float radius) :
    Plane(normal, p), point(p), radius(radius)  { }

float Circle::intersect(const Ray &ray) const {
    float t = Plane::intersect(ray);
    if (t == MAX_FLOAT) return t;
    Point p = ray.getPoint(t);

    return ((point - p).module() <= radius) ? t : MAX_FLOAT;
}

