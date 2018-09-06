#include "Box.h"

Box::Box(const Quad &quad, float height) :
        base(quad), height(height) {

    Dir normal = base.getNormal();

    faces.push_back(make_shared<Quad>(base));

    Point b1, b2, b3, b4;

    tie(b1, b2, b3, b4) = quad.getCorners();

    Point t1 = b1 + normal * -height;
    Point t2 = b2 + normal * -height;
    Point t3 = b3 + normal * -height;
    Point t4 = b4 + normal * -height;

    faces.push_back(make_shared<Quad>(Quad(t1, t2, t3, t4)));
    faces.push_back(make_shared<Quad>(Quad(b1, b2, t1, t2)));
    faces.push_back(make_shared<Quad>(Quad(b2, b4, t2, t4)));
    faces.push_back(make_shared<Quad>(Quad(b3, b4, t3, t4)));
    faces.push_back(make_shared<Quad>(Quad(b3, b1, t3, t1)));

}

void Box::setMaterial(shared_ptr<Material> material) {
    for (const auto &face: faces) {
        face->setMaterial(material);
    }
}

const vector<shared_ptr<Quad>> &Box::getFaces() const {
    return faces;
}

Box Box::moveX(float offset) const {
    return { base.moveX(offset), height };
}

Box Box::moveY(float offset) const {
    return { base.moveY(offset), height };
}

Box Box::moveZ(float offset) const {
    return { base.moveZ(offset), height };
}

void Box::setHeight(float height) {
    Box::height = height;
}



