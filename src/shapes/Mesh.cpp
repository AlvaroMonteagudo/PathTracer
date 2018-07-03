//
// Created by alvaro on 12/06/18.
//

#include <Mesh.h>
#include <fstream>
#include <cstring>
#include <utility>
#include <Triangle.h>
#include <Quad.h>

using namespace std;

Mesh::Mesh(string filename, string alongAxis) :
        filename(std::move(filename)),
        alongAxis(std::move(alongAxis)) {
    loadPlyMesh();
}

const vector<shared_ptr<Shape>> &Mesh::getFaces() const {
    return faces;
}

void Mesh::loadPlyMesh() {
    fstream file(filename, ios::in);

    if (file.is_open()) {
        readHeader(file);
        for (const Element &e: elements) {
            parseElement(e, file);
        }
    } else {
        cout << "Could not open file " << filename << endl;
    }
}

void Mesh::readHeader(fstream &file) {

    string line;
    vector<string> splitted;
    getline(file, line); // Skip first line
    getline(file, line); // Format line

    if (line.find("ascii") == string::npos) {

        cout << "Don't know how to parse other formats but ascii ply files" << endl;
        exit(0);
    }

    do {
        getline(file, line);
        // Find equals 0 = startsWith()
        if (line.find("comment") == 0) continue;
        if (line.find("element") == 0) {
            splitted = split(line, ' ');
            elements.emplace_back(splitted.at(1), stoi(splitted.at(2)));
        }
    } while(line.find("end_header") != 0);
}

void Mesh::parseElement(const tuple<string, int> &tuple, fstream &file) {

    const string &name = get<0>(tuple);
    int number = get<1>(tuple);

    string line;

    if (name == "vertex") {
        for (int i = 0; i < number; ++i) {
            getline(file, line);
            vector<string> splitted = split(line, ' ');
            float x = stof(splitted.at(0)), y = stof(splitted.at(1)), z = stof(splitted.at(2));

            if (x > maxX) {
               maxX = x;
            }
            if (y > maxY) {
                maxY = y;
            }
            if (z > maxZ) {
                maxZ = z;
            }

            if (x < minX) {
                minX = x;
            }
            if (y < minY) {
                minY = y;
            }
            if (z < minZ) {
                minZ = z;
            }

            float max_value = max(maxX, max(maxY, maxZ));
            float min_value = min(minX, min(minY, minZ));
            float DIVISOR = max(abs(max_value), abs(min_value));

            Point p = (alongAxis == "Z") ? Point(x, z, y) :
                      (alongAxis == "X") ? Point(y, x, z) : Point(x, y, z);

            p /= DIVISOR;
            vertices.push_back(p);
        }
    } else if (name == "face") {
        for (int i = 0; i < number; ++i) {
            getline(file, line);
            vector<string> splitted = split(line, ' ');

            int n = stoi(splitted.at(0));

            if (n == 3) {
                int a = stoi(splitted.at(1)), b = stoi(splitted.at(2)), c = stoi(splitted.at(3));
                faces.push_back(make_shared<Triangle>(Triangle(vertices.at(a), vertices.at(b), vertices.at(c))));
            } else if (n == 4) {
                int a = stoi(splitted.at(1)), b = stoi(splitted.at(2)), c = stoi(splitted.at(3)), d = stoi(splitted.at(4));
                faces.push_back(make_shared<Quad>(Quad(vertices.at(a), vertices.at(b), vertices.at(d), vertices.at(c))));
            }

        }
    }
}

void Mesh::setMaterial(shared_ptr<Material> material) {
    for (const auto &face: faces) {
        face->setMaterial(material);
    }
}