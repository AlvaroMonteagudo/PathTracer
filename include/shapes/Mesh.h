#pragma once

#include <string>
#include <vector>
#include <Shape.h>
#include <sstream>
#include <Mat.h>

using namespace std;

class Mesh {

public:

    Mesh(string filename, string alongAxis = "Y");

    const vector<shared_ptr<Shape>> &getFaces() const;

    void loadPlyMesh();

    void readHeader(fstream &fstream);

    void parseElement(const tuple<string, int> &tuple, fstream &file);

    void setMaterial(shared_ptr<Material> material);

    template <class M>
    void setMaterial(M material)
    {
        for (const auto &face : faces)
        {
            face->setMaterial(material);
        }
    }

    vector<string> split(const string &input, char delimitter) {
        vector<string> splitted;
        stringstream ss;
        ss.str(input);
        string item;
        while (getline(ss, item, delimitter)) {
            splitted.push_back(item);
        }
        return splitted;
    }

    float maxX = MIN_FLOAT, maxY = MIN_FLOAT, maxZ = MIN_FLOAT;
    float minX = MAX_FLOAT, minY = MAX_FLOAT, minZ = MAX_FLOAT;

private:

    string filename, alongAxis = "Y";

    std::vector<shared_ptr<Shape>> faces;
    std::vector<Point> vertices;

    typedef std::tuple<string, int> Element;

    std::vector<Element> elements;
};
