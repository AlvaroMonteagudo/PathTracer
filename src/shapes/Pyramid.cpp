
#include "../../include/shapes/Pyramid.h"

Pyramid::Pyramid(const Quad &quad, float height) {
    tie(a, b, c, d) = quad.getCorners();
    center = (a + b + c + d) / 4.0f;
    top = center + quad.getNormal() * -height;
    faces.push_back(make_shared<Quad>(quad));
    faces.push_back(make_shared<Triangle>(Triangle(a, b, top)));
    faces.push_back(make_shared<Triangle>(Triangle(b, c, top)));
    faces.push_back(make_shared<Triangle>(Triangle(c, d, top)));
    faces.push_back(make_shared<Triangle>(Triangle(d, a, top)));

}

Pyramid::Pyramid(const Quad &quad, const Point &top) :
        top(top) {
    tie(a, b, c, d) = quad.getCorners();
    faces.push_back(make_shared<Quad>(quad));
    faces.push_back(make_shared<Triangle>(Triangle(a, b, top)));
    faces.push_back(make_shared<Triangle>(Triangle(b, c, top)));
    faces.push_back(make_shared<Triangle>(Triangle(c, d, top)));
    faces.push_back(make_shared<Triangle>(Triangle(d, a, top)));

}

Pyramid::Pyramid(const Triangle &triangle, float height) {
    tie(a, b, c) = triangle.getCorners();
    center = (a + b + c) / 3.0f;
    top = center + triangle.getNormal() * height;
    faces.push_back(make_shared<Triangle>(triangle));
    faces.push_back(make_shared<Triangle>(Triangle(a, b, top)));
    faces.push_back(make_shared<Triangle>(Triangle(b, c, top)));
    faces.push_back(make_shared<Triangle>(Triangle(c, a, top)));

}

Pyramid::Pyramid(const Triangle &triangle, const Point &top) :
       top(top) {
    tie(a, b, c) = triangle.getCorners();
    faces.push_back(make_shared<Triangle>(triangle));
    faces.push_back(make_shared<Triangle>(Triangle(a, b, top)));
    faces.push_back(make_shared<Triangle>(Triangle(b, c, top)));
    faces.push_back(make_shared<Triangle>(Triangle(c, a, top)));

}

float Pyramid::intersect(const Ray &ray) const {

    float min = MAX_FLOAT;

    for (const shared_ptr<Shape> &face : faces) {
        float dist_face = face->intersect(ray);
        if (dist_face < min) {
            min = dist_face;
        }
    }

    return min;
}

Dir Pyramid::getNormal(const Point &intersectedPoint) const {
    return {1, 0, 0}; // Temporal
}

void Pyramid::setMaterial(const RGB &kd, const RGB &ks, const RGB &kr, const RGB &kt) {
    for (const shared_ptr<Shape> &face: faces) {
        face->setFeatures(kd, ks, kr, kt);
    }
}

