/**
 *  @file    Camera.h
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    12/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Header file for camera class
 *  Abstract camera for ray tracing. Must be defined for a scene.
 */
#pragma once

#define PI 3.14159265358979323846f

#include <ostream>
#include "Point.h"

class Camera {

public:

    /**
     * Empty constructor
     */
    Camera();

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
    Camera(const Dir &up, const Dir &right, const Dir &frontal,
           const Point &focal, float planeDistance,
           int width, int height, float fieldOfView);

    /// GETTERS
    Point getFocal() const;

    Dir getUp() const;

    Dir getRight() const;

    Dir getFrontal() const;

    int getWidth() const;

    int getHeight() const;

    const Point &getFirstPixel() const;

    /**
     * Get size of pixel based on camera parameters
     * @return pixel size for image plane
     */
    float getPixelSize() const;

    /**
     * Calculate size of pixel based on camera parameters
     */
    void calculatePixelSize();

    /**
     * Calculate point where it is the first pixel, used to iterate over pixels in image plane
     */
    void calculateFirstPixel();

    /**
     * Print data method for camera
     * @param os: stream to be overwritten
     * @param d: camera dataa
     * @return camera data printed in os
     */
    friend std::ostream& operator << (std::ostream &os, const Camera &d);

private:

    /// CAMERA PARAMETERS
    Dir up, right, frontal;

    Point focal;

    float planeDistance;

    int width, height;

    float pixelSize;

    float fieldOfView;

    Point firstPixel;

};
