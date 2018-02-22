//
// Created by alvaro on 9/01/18.
//


#include "AreaLight.h"


AreaLight::AreaLight(const Point &upCorner, const Point &downCorner, const Dir &normal, const Dir &xDir, const Dir &yDir,
                     float intensity)
            : Plane(normal, upCorner),
              upCorner(upCorner),
              downCorner(downCorner),
              intensity(intensity){

    maxValues = Point(max(upCorner.x, downCorner.x),
                      max(upCorner.y, downCorner.y),
                      max(upCorner.z, downCorner.z));

    minValues = Point(min(upCorner.x, downCorner.x),
                      min(upCorner.y, downCorner.y),
                      min(upCorner.z, downCorner.z));

}

float AreaLight::intersect(const Ray &ray) const {
    float value = Plane::intersect(ray);

    Point intersectedPoint = ray.getSource() + ray.getDirection() * value;

    if ((minValues <= intersectedPoint) & (maxValues >= intersectedPoint)) {
        return value;
    } else {
        return MAX_FLOAT;
    }
}


