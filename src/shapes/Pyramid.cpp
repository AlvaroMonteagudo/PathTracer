
#include "Pyramid.h"

Pyramid::Pyramid(const Quad &quad, float height) {
    tie(a, b, c, d) = quad.getCorners();
    center = quad.getCenter();
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
    center = triangle.getCenter();
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


void Pyramid::setMaterial(shared_ptr<Material> material) {
    for (const shared_ptr<Shape> &face: faces) {
        face->setMaterial(material);
    }
}

const vector<shared_ptr<Shape>> &Pyramid::getFaces() const {
    return faces;
}

