
#include <Texture.h>
#include <utility>
#include <iostream>
#include <sstream>

Texture::Texture(string _filename) :
        Material(),
        filename(std::move(_filename)) {
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
        // mensaje
    }

    textArray = new RGB[width * height];

    // Read comments
    do {
        getline(file, line);
    } while (line.find('#') == 0);

    line_buffer.str(line);

    line_buffer >>  maxRGBValue;

    float r, g, b;

    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            file >> r >> g >> b;
            r = (r > 242) ? 242 : r;
            g = (g > 242) ? 242 : g;
            b = (b > 242) ? 242 : b;

            cout << r << g << b << endl;

            textArray[i * width + j] = RGB(r, g, b);
        }
    }
}
