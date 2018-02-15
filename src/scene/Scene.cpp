/**
 *  @file    Scene.cpp
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    18/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Implementation for scene class
 */


#include <sstream>
#include <cstring>
#include "../../include/scene/Scene.h"


/**
 * Default constructor
 */
Scene::Scene() {
    // Dir es normal,
    Plane rightWall(Plane(Dir(-1, 0, 0), Point(1, 0, 0)));
    rightWall.setFeatures(RED, BLACK, BLACK, BLACK);

    Plane leftWall(Plane(Dir(1, 0, 0), Point(-1, 0, 0)));
    leftWall.setFeatures(GREEN, BLACK, BLACK, BLACK);

    Plane floor(Plane(Dir(0, 1, 0), Point(0, -1, 0)));
    floor.setFeatures(GRAY, BLACK, BLACK, BLACK);

    Plane ceiling(Plane(Dir(0, -1, 0), Point(0, 1, 0)));
    ceiling.setFeatures(GRAY, BLACK, BLACK, BLACK);

    Plane bottom(Plane(Dir(0, 0, -1), Point(0, 0, 1)));
    bottom.setFeatures(GRAY, BLACK, BLACK, BLACK);

    Plane backWall(Plane(Dir(0, 0, 1), Point(0, 0, -2)));
    backWall.setFeatures(GRAY, BLACK, BLACK, BLACK);

    Sphere leftSphere(Sphere(0.25f, Point(-0.5f, 0, 0.4f)));
    leftSphere.setFeatures(RED, BLACK, BLACK, BLACK);

    Sphere rightSphere(Sphere(0.25f, Point(0.5f, 0, 0.4f)));
    rightSphere.setFeatures(GREEN, BLACK, BLACK, BLACK);

    setCamera(Camera(Dir(0, 1, 0), Dir(1, 0, 0), Dir(0, 0, 1),
                    Point(0.f, -0.f, -2.8f), 1.0, 720, 720, PI/3.0f));

    LightSource light = LightSource(Point(0.0f, 0.8f, -0.3f), 1.5f);

    lights.push_back(light);

    shapes.push_back(make_shared<Plane>(rightWall));
    shapes.push_back(make_shared<Plane>(leftWall));
    shapes.push_back(make_shared<Plane>(floor));
    shapes.push_back(make_shared<Plane>(ceiling));
    //shapes.push_back(make_shared<Sphere>(leftSphere));
    //shapes.push_back(make_shared<Sphere>(rightSphere));
    shapes.push_back(make_shared<Plane>(bottom));
    //shapes.push_back(make_shared<Plane>(backWall));
    //shapes.push_back(make_shared<Sphere>(airSphere));
    //shapes.push_back(make_shared<Sphere>(waterSphere));
    //shapes.push_back(make_shared<Sphere>(glassSphere));
}


/**
 * Default constructor
 */
/*Scene::Scene() {
    // Dir es normal,
    Plane rightWall(Plane(Dir(-1, 0, 0), Point(1, 0, 0)));
    rightWall.setFeatures(GREEN, BLACK, BLACK, BLACK);

    Plane leftWall(Plane(Dir(1, 0, 0), Point(-1, 0, 0)));
    leftWall.setFeatures(RED, BLACK, BLACK, BLACK);

    Plane floor(Plane(Dir(0, 1, 0), Point(0, -1, 0)));
    floor.setFeatures(GRAY, BLACK, BLACK, BLACK);

    Plane ceiling(Plane(Dir(0, -1, 0), Point(0, 1, 0)));
    ceiling.setFeatures(GRAY, BLACK, BLACK, BLACK);

    Plane bottom(Plane(Dir(0, 0, -1), Point(0, 0, 1)));
    bottom.setFeatures(BLUE, BLACK, BLACK, BLACK);

    Plane backWall(Plane(Dir(0, 0, 1), Point(0, 0, -2)));
    backWall.setFeatures(GRAY, BLACK, BLACK, BLACK);

    Sphere leftSphere(Sphere(0.6f, Point(0, 0, 0)));
    leftSphere.setFeatures(BLACK, BLACK, BLACK, WHITE);
    leftSphere.setRefractiveIndex(20);

    Sphere rightSphere(Sphere(0.3f, Point(0.68f, -0.68f, 0.55f)));
    rightSphere.setFeatures(BLACK, BLACK, BLACK, WHITE);
    rightSphere.setRefractiveIndex(WATER);

    Sphere center(Sphere(0.3f, Point(0, -0.6f, 0.3f)));
    center.setFeatures(GREEN, BLACK, BLACK, BLACK);

    Sphere back(Sphere(0.15f, Point(0.5f, -0.2f, 0.8f)));
    back.setFeatures(BLUE, BLACK, BLACK, BLACK);

    setCamera(Camera(Dir(0, 1, 0), Dir(1, 0, 0), Dir(0, 0, 1),
                     Point(0.f, -0.f, -1.8f), 1.0, 1080, 1080, PI/3.0f));

    LightSource light = LightSource(Point(0.0f, 0.8f, -0.3f), 2.5f);

    lights.push_back(light);

    shapes.push_back(make_shared<Plane>(rightWall));
    shapes.push_back(make_shared<Plane>(leftWall));
    shapes.push_back(make_shared<Plane>(floor));
    shapes.push_back(make_shared<Plane>(ceiling));
    shapes.push_back(make_shared<Plane>(bottom));
    shapes.push_back(make_shared<Plane>(backWall));
    shapes.push_back(make_shared<Sphere>(leftSphere));
    //shapes.push_back(make_shared<Sphere>(rightSphere));
    //shapes.push_back(make_shared<Sphere>(center));
    //shapes.push_back(make_shared<Sphere>(back));
}*/


/**
 * Scene constructor
 * @param filename where scene specifications are
 */
Scene::Scene(string filename){

    setCamera(Camera(Dir(0, 1, 0), Dir(1, 0, 0), Dir(0, 0, 1),
                     Point(0.f, -0.25f, -1.7f), 1.0, 1920, 1080, PI/3.0f));

    LightSource light = LightSource(Point(0, 0.6f, -0.1f), 2.0f);

    lights.push_back(light);

    std::ifstream infile;
    infile.open(filename);

    string line;
    while (!infile.eof()) {
        std::getline(infile, line);
        std::istringstream iss(line);
        if (line.find('#') == string::npos) {
            string item;
            iss >> item;
            if (strcmp(item.c_str(), "Plane") == 0) {
                addPlane(infile);
            } else if (strcmp(item.c_str(), "Sphere") == 0) {
                addSphere(infile);
            }
        }
    }
}

/**
 * Get camera used in this scene
 * @return camera used in this scene
 */
const Camera &Scene::getCamera() const {
    return camera;
}

/**
 * Set camera values of this scene
 * @param camera
 */
void Scene::setCamera(const Camera &camera) {
    Scene::camera = camera;
}

/**
 * Get shapes usd in this scene
 * @return vector with shapes of this scene
 */
const std::vector<std::shared_ptr<Shape>> &Scene::getShapes() const {
    return shapes;
}

/**
 * Get lights usd in this scene
 * @return vector with lights of this scene
 */
const std::vector<LightSource> &Scene::getLights() const {
    return lights;
}

/**
 * Get area lights usd in this scene
 * @return vector with area lights of this scene
 */
const std::vector<AreaLight> &Scene::getAreaLights() const {
    return areaLights;
}

/// Methods to set scene features stored in a file


void Scene::addPlane(ifstream & infile) {
    float x, y, z;

    RGB kd, ks, kr, kt;
    Point point{};
    Dir normal{};
    float shininess = 0.0, refractiveIndex = AIR_RI;

    string line, trash;
    while (line.find('}') == string::npos) {
        std::getline(infile, line);
        std::istringstream iss(line);

        if (line.find("Point") != string::npos) {
            iss >> trash >> x >> y >> z;
            point = Point(x, y, z);
        } else if (line.find("Normal") != string::npos) {
            iss >> trash >> x >> y >> z;
            normal = Dir(x, y, z);
        } else if (line.find("Shininess") != string::npos) {
            iss >> trash >> shininess;
        } else if (line.find("Refractive") != string::npos) {
            iss >> trash >> refractiveIndex;
        } else if (line.find("Material") != string::npos) {
            std::getline(infile, line);
            while (line.find('}') == string::npos) {
                parseMaterial(line, kd, ks, kr, kt);
                std::getline(infile, line);
            }
            std::getline(infile, line); // Ultimo '}'
        }
    }
    Plane plane = Plane(normal, point);
    plane.setFeatures(kd, ks, kr, kt);
    plane.setShininess(shininess);
    plane.setRefractiveIndex(refractiveIndex);
    shapes.push_back(make_shared<Plane>(plane));
}

void Scene::addSphere(ifstream & infile) {
    float x, y, z;

    RGB kd, ks, kr, kt;
    Point point{};
    float radius = 2, shininess = 0.0, refractiveIndex = AIR_RI;

    string line, trash;
    while (line.find('}') == string::npos) {
        std::getline(infile, line);
        std::istringstream iss(line);

        if (line.find("Point") != string::npos) {
            iss >> trash >> x >> y >> z;
            point = Point(x, y, z);
        } else if (line.find("Radius") != string::npos) {
            iss >> trash >> radius;
        } else if (line.find("Shininess") != string::npos) {
            iss >> trash >> shininess;
        } else if (line.find("Refractive") != string::npos) {
            iss >> trash >> refractiveIndex;
        } else if (line.find("Material") != string::npos) {
            std::getline(infile, line);
            while (line.find('}') == string::npos) {
                parseMaterial(line, kd, ks, kr, kt);
                std::getline(infile, line);
            }
            std::getline(infile, line); // Ultimo '}'
        }
    }
    Sphere sphere = Sphere(radius, point);
    sphere.setFeatures(kd, ks, kr, kt);
    sphere.setShininess(shininess);
    sphere.setRefractiveIndex(refractiveIndex);
    shapes.push_back(make_shared<Sphere>(sphere));
}

void Scene::parseMaterial(const string &line, RGB &kd, RGB &ks, RGB &kr, RGB &kt) {
    float r, g, b;
    string trash;
    std::istringstream iss(line);
    if (line.find("Diffuse") != string::npos) {
        iss >> trash >> r >> g >> b;
        kd = RGB(r / 255.0f, g / 255.0f, b / 255.0f);
    } else if (line.find("Specular") != string::npos) {
        iss >> trash >> r >> g >> b;
        ks = RGB(r / 255.0f, g / 255.0f, b / 255.0f);
    } else if (line.find("Reflectance") != string::npos) {
        iss >> trash >> r >> g >> b;
        kr = RGB(r / 255.0f, g / 255.0f, b / 255.0f);
    } else if (line.find("Transmittance") != string::npos) {
        iss >> trash >> r >> g >> b;
        kt = RGB(r / 255.0f, g / 255.0f, b / 255.0f);
    }
}


