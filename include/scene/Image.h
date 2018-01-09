/**
 *  @file    Image.h
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    15/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Header file for image class
 *  Keeps color for each pixel, moreover it save the resulting image after
 *  ray tracing.
 */

#pragma once

#include "RGB.h"
#include <string>

using namespace std;

class Image {

public:

    /**
     * Default constructor
     */
    Image();

    /**
     * Image constructor
     * @param width of the image
     * @param height of the image
     */
    Image(int width, int height);

    /// GETTERS
    int getWidth() const;

    int getHeight() const;

    /**
     * Save image method
     * @param filename: name of the file to be saved
     */
    void saveImage(string filename)const;

    /**
     * Access operator to matrix element, use to update or to get value
     * @param row index
     * @param col index
     * @return RGB value stored in im(row, col)
     */
    RGB & operator ()(int row, int col) const;

private:

    /// IMAGE PARAMETERS
    int width, height;

    RGB * imArray;

};
