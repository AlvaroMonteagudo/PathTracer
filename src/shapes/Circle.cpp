#include "Circle.h"

Circle::Circle(const Point &p, const Dir &normal, float radius) :
    Plane(normal, p), point(p), radius(radius)  { }

float Circle::intersect(const Ray &ray) const {
    float t = Plane::intersect(ray);
    if (t == MAX_FLOAT) return t;
    Point p = ray.getPoint(t);

    return ((point - p).module() <= radius) ? t : MAX_FLOAT;
}

const Point &Circle::getPoint() const {
    return point;
}

float Circle::getRadius() const {
    return radius;
}

Circle Circle::moveX(const float offset) const {
    return { point.moveX(offset), Plane::getNormal(), radius };
}

Circle Circle::moveY(float offset) const {
    return { point.moveY(offset), Plane::getNormal(), radius  };
}

Circle Circle::moveZ(float offset) const {
    return { point.moveZ(offset), Plane::getNormal(), radius };
}

void Circle::setRadius(float radius) {
    Circle::radius = radius;
}

