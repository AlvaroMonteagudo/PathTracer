#pragma once

#include <string>
#include "RGB.h"
#include "Material.h"

using namespace std;

class Texture : public Material {

public:

    Texture(string filename, string lockedDimension, float divisor);

    const RGB &getKd(const Point& point) const;

    void readPPMFIle();

private:

    string filename, lockedDimension;

    int width, height, maxRGBValue;

    float divisor;

    RGB * rgbArray;
};