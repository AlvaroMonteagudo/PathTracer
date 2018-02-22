/**
 *  @file    Camera.cpp
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    12/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Implementation for camera class
 */
#include "Camera.h"

/**
 * Empty constructor
 */
Camera::Camera() :
    up(0,1,0), right(1,0,0), frontal(0,0,1), focal(0,0,0),
    planeDistance(1.0), width(256), height(256), fieldOfView(PI/4.0f) {

    calculatePixelSize();
}

/**
 * Camera constructor
 * @param up: vertical axis
 * @param right: right axis
 * @param frontal: frontal axis
 * @param focal point where camera is placed
 * @param planeDistance: distance to image plane
 * @param width of image plane
 * @param height of image plane
 * @param fieldOfView from which is seen the image plane
 */
Camera::Camera(const Dir &up, const Dir &right, const Dir &frontal,
               const Point &focal, const float planeDistance,
               int width, int height, const float fieldOfView) :
                up(up), right(right), frontal(frontal), focal(focal),
                planeDistance(planeDistance), width(width), height(height),
                fieldOfView(fieldOfView) {

    calculatePixelSize();
}

/// GETTERS

Dir Camera::getUp() const {
    return up;
}

Dir Camera::getRight() const {
    return right;
}

Dir Camera::getFrontal() const {
    return frontal;
}

Point Camera::getFocal() const {
    return focal;
}

int Camera::getWidth() const {
    return width;
}

int Camera::getHeight() const {
    return height;
}

const Point &Camera::getFirstPixel() const {
    return firstPixel;
}

/**
 * Get size of pixel based on camera parameters
 * @return pixel size for image plane
 */
float Camera::getPixelSize() const {
    return pixelSize;
}

/**
 * Calculate size of pixel based on camera parameters
 */
void Camera::calculatePixelSize() {
    pixelSize = static_cast<float> ((2.0 * tan(fieldOfView / 2.0)) / height);
}

/**
 * Calculate point where it is the first pixel, used to iterate over pixels in image plane
 */
void Camera::calculateFirstPixel() {
    Point middle = focal + frontal * planeDistance;
    Point first = middle - right * (((width - 1 ) / 2.0) * pixelSize)
                  + up * (((height - 1 ) / 2.0) * pixelSize);
    firstPixel = first;
}

/**
 * Print data method for camera
 * @param os: stream to be overwritten
 * @param d: camera dataa
 * @return camera data printed in os
 */
std::ostream& operator << (std::ostream &os, const Camera &c){
    os << "Camara(" << endl <<
       "  Up      (" << c.getUp().x << ", " << c.getUp().y << ", "<< c.getUp().z << ") " << endl <<
       "  Right   (" << c.getRight().x << ", " << c.getRight().y << ", "<< c.getRight().z << ") " << endl <<
       "  Frontal (" << c.getFrontal().x << ", " << c.getFrontal().y << ", "<< c.getFrontal().z << ") " << endl <<
       "  Focal   (" << c.getFocal().x << ", " << c.getFocal().y << ", "<< c.getFocal().z << ") " << endl <<
       ")" << endl;
    return os;
}