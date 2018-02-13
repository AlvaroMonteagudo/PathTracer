/**
 *  @file    RGB.cpp
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    15/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Implementation for RGB class
 */

#include <iostream>
#include "../../include/scene/RGB.h"

/**
 * Color constructor
 * @param red value
 * @param green value
 * @param blue value
 */
RGB::RGB(float red = 0, float green = 0, float blue = 0) {

    RGB::red = red;
    RGB::green = green;
    RGB::blue = blue;
}

/// GETTERS

float RGB::getRed() const {
    return red;
}

float RGB::getGreen() const {
    return green;
}

float RGB::getBlue() const {
    return blue;
}

float RGB::getMean() const {
    return (red + blue + green) / 3.0f;
}

float RGB::getMax() const {
    return max(red, max(blue, green));
}

/// Useful operators

std::ostream& operator << (std::ostream &os, const RGB &rgb){
    os << "RGB(" << rgb.getRed() << "," << rgb.getGreen() << "," << rgb.getBlue() << ")" << endl;
    return os;
}

std::ofstream& operator << (std::ofstream &file, const RGB &rgb){
    file << " " << (int) (rgb.getRed() * 255)
         << " " << (int) (rgb.getGreen() * 255)
         << " " << (int) (rgb.getBlue() * 255) << '\t';
    return file;
}

RGB RGB::operator + (const RGB &color) const {
    return { red + color.getRed(), green + color.getGreen(), blue + color.getBlue()  };
}

void RGB::operator += (const RGB &color) {
    red += color.getRed();
    green += color.getGreen();
    blue += color.getBlue();
}

RGB RGB::operator * (const RGB &color) const {
    return { red * color.getRed(), green * color.getGreen(), blue * color.getBlue() };
}

void RGB::operator *= (const RGB &color) {
    red *= color.getRed();
    green *= color.getGreen();
    blue *= color.getBlue();
}

RGB RGB::operator * (float value) const {
    return { red * value, green * value, blue * value  };
}

void RGB::operator *= (float value) {
    red *= value;
    green *= value;
    blue *= value;
}

RGB RGB::operator / (float value) const {
    return { red / value, green / value, blue / value  };
}

void RGB::operator /= (float value) {
    red /= value;
    green /= value;
    blue /= value;
}

bool RGB::operator==(const RGB &rhs) const {
    return red == rhs.red &&
            green == rhs.green &&
            blue == rhs.blue;
}

bool RGB::operator!=(const RGB &rhs) const {
    return !(rhs == *this);
}
