/**
 *  @file    Image.cpp
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    15/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Implementation for image class
 */

#include "Image.h"
#include <fstream>
#include <iostream>

/**
 * Default constructor
 */
Image::Image() = default;

/**
 * Image constructor
 * @param width of the image
 * @param height of the image
 */
Image::Image(int width, int height) : width(width), height(height) {
    imArray = new RGB[width * height];
}

/// GETTERS

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

/**
 * Access operator to matrix element, use to update or to get value
 * @param row index
 * @param col index
 * @return RGB value stored in im(row, col)
 */
RGB & Image::operator()(int row, int col) const {
    return imArray[(row*width) + col];
}

/**
 * Save image method
 * @param filename: name of the file to be saved
 */
void Image::saveImage(string filename)const {
    ofstream file(filename);

    file << "P3\n"
         << width << " " << height << '\n'
         << "# " << filename << '\n'
         << "255\n";

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            file << (*this)(i,j).toInt() << '\t';
        }
        file << '\n';
    }

    file.close();

    std::cout << "Image saved in " << filename << std::endl;
    string command = "eog " + filename +  " &";

    system(command.c_str());
    //exit(0);
}




