
#include "Pyramid4.h"

Pyramid4::Pyramid4(const Quad &quad, float height) :
    base(quad), height(height) {

    tie(a, b, c, d) = base.getCorners();
    center = quad.getCenter();
    top = center + quad.getNormal() * -height;
    faces.push_back(make_shared<Quad>(quad));
    faces.push_back(make_shared<Triangle>(Triangle(a, b, top)));
    faces.push_back(make_shared<Triangle>(Triangle(b, d, top)));
    faces.push_back(make_shared<Triangle>(Triangle(d, c, top)));
    faces.push_back(make_shared<Triangle>(Triangle(c, a, top)));

}

Pyramid4::Pyramid4(const Quad &quad, const Point &top) :
        base(quad), height(height), top(top) {

    tie(a, b, c, d) = quad.getCorners();
    faces.push_back(make_shared<Quad>(quad));
    faces.push_back(make_shared<Triangle>(Triangle(a, b, top)));
    faces.push_back(make_shared<Triangle>(Triangle(b, d, top)));
    faces.push_back(make_shared<Triangle>(Triangle(d, c, top)));
    faces.push_back(make_shared<Triangle>(Triangle(c, a, top)));

}


void Pyramid4::setMaterial(shared_ptr<Material> material) {
    for (const shared_ptr<Shape> &face: faces) {
        face->setMaterial(material);
    }
}

const vector<shared_ptr<Shape>> &Pyramid4::getFaces() const {
    return faces;
}

Pyramid4 Pyramid4::moveX(float offset) const {
    if (height > 0.0) {
        return {base.moveX(offset), height};
    } else {
        return {base.moveX(offset), top};
    }
}

Pyramid4 Pyramid4::moveY(float offset) const {
    if (height > 0.0) {
        return {base.moveY(offset), height};
    } else {
        return {base.moveY(offset), top};
    }
}

Pyramid4 Pyramid4::moveZ(float offset) const {
    if (height > 0.0) {
        return {base.moveZ(offset), height};
    } else {
        return {base.moveZ(offset), top};
    }
}

void Pyramid4::setHeight(float height) {
    Pyramid4::height = height;
}

const Quad &Pyramid4::getBase() const {
    return base;
}

