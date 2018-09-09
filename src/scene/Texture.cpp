
#include <Texture.h>
#include <utility>
#include <iostream>
#include <sstream>

Texture::Texture(string _filename, string _lockedDimension, float divisor) :
        Material(),
        filename(std::move(_filename)),
        divisor(divisor),
        lockedDimension(std::move(_lockedDimension)){
    readPPMFIle();
}

void Texture::readPPMFIle() {

    fstream file(filename, ios::in);
    string line;
    stringstream line_buffer;


    if (!file.good()) {
        cout << "Could not read " << filename << endl;
        exit(1);
    }

    // Read comments
    do {
        getline(file, line);
    } while (line.find('#') == 0);

    if (line != "P3") {
        cout << "I am only able to read P3 PPM files" << endl;
        exit(1);
    }

    // Read comments
    do {
        getline(file, line);
    } while (line.find('#') == 0);

    line_buffer.str(line);

    line_buffer >> width >> height;

    if (width == 0 || height == 0) {
        cerr << "Couldn't parse PPM width and height" << endl;
    }

    rgbArray = new RGB[width * height];

    // Read comments
    do {
        getline(file, line);
    } while (line.find('#') == 0);

    line_buffer.clear();
    line_buffer.str(line);

    line_buffer >> maxRGBValue;

    float r, g, b;

    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            file >> r >> g >> b;
            r = (r > 242 ? 242 : r) / maxRGBValue;
            g = (g > 242 ? 242 : g) / maxRGBValue;
            b = (b > 242 ? 242 : b) / maxRGBValue;

            rgbArray[i * width + j] = RGB(r, g, b);
        }
    }
}

const RGB &Texture::getKd(const Point &point) const {
    auto x = static_cast<int>((point.x < 0 ? -point.x : point.x) / divisor);
    auto y = static_cast<int>((point.y < 0 ? -point.y : point.y) / divisor);
    auto z = static_cast<int>((point.z < 0 ? -point.z : point.z) / divisor);

    //cout << x << " " << y << " " << z << endl;

    if (lockedDimension == "X") {
        return rgbArray[(y % height) * width + (z % width)];
    } else if (lockedDimension == "Y") {
        return rgbArray[(z % height) * width + (x % width)];
    } else if (lockedDimension == "Z") {
        return rgbArray[(y % height) * width + (x % width)];
    }
}
