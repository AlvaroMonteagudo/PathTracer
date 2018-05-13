#include "Box.h"

Box::Box(const Quad &quad, const float depth) {

    Dir normal = quad.getNormal();

    faces.push_back(make_shared<Quad>(quad));

    Point b1, b2, b3, b4;

    tie(b1, b2, b3, b4) = quad.getCorners();

    Point t1 = b1 + normal * -depth;
    Point t2 = b2 + normal * -depth;
    Point t3 = b3 + normal * -depth;
    Point t4 = b4 + normal * -depth;

    faces.push_back(make_shared<Quad>(Quad(t1, t2, t3, t4)));
    faces.push_back(make_shared<Quad>(Quad(b1, b2, t2, t1)));
    faces.push_back(make_shared<Quad>(Quad(b2, b3, t3, t2)));
    faces.push_back(make_shared<Quad>(Quad(b3, b4, t4, t3)));
    faces.push_back(make_shared<Quad>(Quad(b4, b1, t1, t4)));

}

void Box::setMaterial(shared_ptr<Material> material) {
    for (const auto &face: faces) {
        face->setMaterial(material);
    }
}

const vector<shared_ptr<Quad>> &Box::getFaces() const {
    return faces;
}
