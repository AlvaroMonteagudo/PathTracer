#include "Box.h"

Box::Box(const Quad &quad, const float depth) : Shape() {

    Dir normal = quad.getNormal();

    faces[0] = (make_shared<Quad>(quad));

    Point b1, b2, b3, b4;

    tie(b1, b2, b3, b4) = quad.getCorners();

    Point t1 = b1 + normal * -depth;
    Point t2 = b2 + normal * -depth;
    Point t3 = b3 + normal * -depth;
    Point t4 = b4 + normal * -depth;

    faces[1] = (make_shared<Quad>(Quad(t1, t2, t3, t4)));
    faces[2] = (make_shared<Quad>(Quad(b1, b2, t2, t1)));
    faces[3] = (make_shared<Quad>(Quad(b2, b3, t3, t2)));
    faces[4] = (make_shared<Quad>(Quad(b3, b4, t4, t3)));
    faces[5] = (make_shared<Quad>(Quad(b4, b1, t1, t4)));

}

float Box::intersect(const Ray &ray) const {

    float min = MAX_FLOAT;

    for (const shared_ptr<Quad> &face : faces) {
        float dist_face = face->intersect(ray);
        if (dist_face < min) {
            min = dist_face;
        }
    }

    return min;
}

Dir Box::getNormal(const Point &intersectedPoint) const {
   return {1, 0, 0}; // Temporal
}

void Box::setMaterial(const RGB &kd, const RGB &ks, const RGB &kr, const RGB &kt) {
    for (const shared_ptr<Quad> &face: faces) {
        face->setFeatures(kd, ks, kr, kt);
    }
}
