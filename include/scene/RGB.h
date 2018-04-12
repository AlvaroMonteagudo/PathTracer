/**
 *  @file    RGB.h
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    15/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Header file for RGB class
 *  Color definition with three values: red, green and blue.
 *  It could be enlarge to handle HSV, HSL or other diferent kind of
 *  color representations.
 */

#pragma once

#include <ostream>
#include <fstream>

using namespace std;

class RGB{

public:

    /**
     * Color constructor
     * @param red value
     * @param green value
     * @param blue value
     */
    RGB(float red = 0, float green = 0, float blue = 0);

    /// GETTERS
    float getRed() const;

    float getBlue() const;

    float getGreen() const;

    float getMean() const;

    float getMax() const;

    /// Useful operators
    RGB operator + (const RGB &color) const;

    void operator += (const RGB &color);

    RGB operator * (const RGB &color) const;

    void operator *= (const RGB &color) ;

    RGB operator * (float value) const;

    void operator *= (float value);

    RGB operator / (float value) const;

    void operator /= (float value);

    bool operator ==(const RGB &rhs) const;

    bool operator !=(const RGB &rhs) const;

    friend std::ostream& operator << (std::ostream &os, const RGB &rgb);

    /**
     * Operator to write color to a file
     * @param file to write color
     * @param rgb data to be written
     * @return file with rgb data values written
     */
    friend std::ofstream& operator << (std::ofstream &file, const RGB &rgb);

    RGB toInt();


private:

    float red, blue, green;

};

/// RGB common used values
#define WHITE   RGB(1.0f, 1.0f, 1.0f) * .9
#define BLACK   RGB(0, 0, 0)
#define RED     RGB(0.9f, 0, 0)
#define GREEN   RGB(0, 0.9f, 0)
#define BLUE    RGB(0, 0, 0.9f)
#define GRAY    RGB(0.5, 0.5, 0.5)
#define PURPLE  RGB(0.85f, 0.2f, 1.0f)
#define ORANGE  RGB(0.85f, 0.55f, 0.2f)
#define YELLOW  RGB(0.85f, 0.85f, 0.3f)
#define L_GRAY  GRAY * 1.25f
#define D_GRAY  GRAY * 0.75f