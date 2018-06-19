#pragma once

#include <string>
#include "RGB.h"
#include "Material.h"

using namespace std;

class Texture : public Material {

public:

    Texture(string filename);

    void readPPMFIle();

private:

    string filename;

    int width, height, maxRGBValue;

    RGB * textArray;
};