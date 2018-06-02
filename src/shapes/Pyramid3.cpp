//
// Created by alvaro on 13/05/18.
//

#include "Pyramid3.h"

Pyramid3::Pyramid3(const Triangle &triangle, float height) :
        base(triangle), height(height) {

    tie(a, b, c) = triangle.getCorners();
    center = triangle.getCenter();
    top = center + triangle.getNormal() * -height;
    faces.push_back(make_shared<Triangle>(triangle));
    faces.push_back(make_shared<Triangle>(Triangle(a, b, top)));
    faces.push_back(make_shared<Triangle>(Triangle(b, c, top)));
    faces.push_back(make_shared<Triangle>(Triangle(c, a, top)));

}

Pyramid3::Pyramid3(const Triangle &triangle, const Point &top) :
        base(triangle), height(height), top(top) {

    tie(a, b, c) = triangle.getCorners();
    faces.push_back(make_shared<Triangle>(triangle));
    faces.push_back(make_shared<Triangle>(Triangle(a, b, top)));
    faces.push_back(make_shared<Triangle>(Triangle(b, c, top)));
    faces.push_back(make_shared<Triangle>(Triangle(c, a, top)));

}


void Pyramid3::setMaterial(shared_ptr<Material> material) {
    for (const shared_ptr<Shape> &face: faces) {
        face->setMaterial(material);
    }
}

const vector<shared_ptr<Shape>> &Pyramid3::getFaces() const {
    return faces;
}

Pyramid3 Pyramid3::moveX(float offset) const {
    if (height > 0.0) {
        return {base.moveX(offset), height};
    } else {
        return {base.moveX(offset), top};
    }
}

Pyramid3 Pyramid3::moveY(float offset) const {
    if (height > 0.0) {
        return {base.moveY(offset), height};
    } else {
        return {base.moveY(offset), top};
    }
}

Pyramid3 Pyramid3::moveZ(float offset) const {
    if (height > 0.0) {
        return {base.moveZ(offset), height};
    } else {
        return {base.moveZ(offset), top};
    }
}

void Pyramid3::setHeight(float height) {
    Pyramid3::height = height;
}

