//
// Created by alvaro on 22/05/18.
//

#include "Cylinder.h"

Cylinder::Cylinder() = default;


Cylinder::Cylinder(const Point &_point, const Dir &_axis, float _radius) :
        Shape(), point(_point), axis(_axis),
        radius(_radius), sqrd_radius(_radius * _radius) {
    if ((_axis != X_AXIS) && (_axis != Y_AXIS) && (_axis != Z_AXIS)) {
        cerr << "Cylinders can only be created aligned to x, y or z axis(unit positive vectors" << endl;
    }
    if (_axis == X_AXIS) point.x = 0;
    else if (_axis == Y_AXIS) point.y = 0;
    else point.z = 0;
}


float Cylinder::intersect(const Ray &ray) const {
    Dir A = (ray.getDirection() - axis * (ray.getDirection().dot(axis)));
    Dir dP = ray.getSource() - point;
    Dir B = dP - axis * dP.dot(axis);
    float a = A.dot(A);
    float b = 2 * (A.dot(B));
    float c = B.dot(B) - sqrd_radius;

    return solveQuadratic(a, b, c);
}

Dir Cylinder::getNormal(const Point &intersectedPoint) const {

    return (axis == X_AXIS) ? Dir(0, intersectedPoint.y - point.y, intersectedPoint.z - point.z).normalize() :
           (axis == Y_AXIS) ? Dir(intersectedPoint.x - point.x, 0, intersectedPoint.z - point.z).normalize() :
                              Dir(intersectedPoint.x - point.x, intersectedPoint.y - point.y, 0).normalize();
}

