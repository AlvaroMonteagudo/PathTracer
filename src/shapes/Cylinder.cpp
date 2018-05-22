//
// Created by alvaro on 22/05/18.
//

#include "Cylinder.h"

Cylinder::Cylinder(Circle &base, float height) :
        base(base), height(height), top(base.moveX(height)){ }


float Cylinder::intersect(const Ray &ray) const {

}

Dir Cylinder::getNormal(Point &intersectedPoint) {
    return Dir();
}
