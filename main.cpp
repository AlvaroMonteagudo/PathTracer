/**
 *  @file    main.cpp
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    30/09/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Main class for ray trace implemented algorithm, modifiable attributes are allowed
 *  to personalize execution of the algorithm, such as indirect steps, depth of ray trace...
 */

#include <iostream>
#include <queue>
#include <list>
#include <string>
#include <algorithm>
#include "Scene.h"
#include "Tracer.h"

void printUsage();

string currentDate();

using namespace std;

int main(int argc, char * argv[]){

    string sceneStr = "cornell", fileName = "../images/image" + currentDate() + ".ppm";
    int indirectSamples = 128, width = 720, height = 720;

    vector<string> arguments;
    vector<string> scenes = { "cornell", "cornell_holes", "sphere_materials", "specular_spheres",
                              "boxes", "window", "many_lights", "hole", "hidden_mirror" };

    for (int i = 1; i < argc; ++i) {
        arguments.emplace_back(argv[i]);
    }

    for (unsigned long j = 0; j < arguments.size(); ++j) {
        if (arguments.at(j) == "-s" || arguments.at(j) == "--scene") {
            ++j;
            std::list<std::string>::iterator it;

            if (j > argc) {
                cout << "Scene not provided, a cornell box will be rendered" << endl;
            } else if (std::find(scenes.begin(), scenes.end(), arguments.at(j)) != scenes.end()) {
                sceneStr = arguments.at(j);
            } else {
                cout << "Unable to find " << arguments.at(j) << " as a scene. Try one of the list" << endl;
                for (const auto &scene : scenes) {
                    cout << "\t- " << scene << endl;
                }
                return 0;
            }
        } else if (arguments.at(j) == "-p" || arguments.at(j) == "--paths"){
            ++j;
            if (j > argc) {
                cout << "Using default number of paths = 128, number not provided." << endl;
            } else {
                indirectSamples = stoi(arguments.at(j));
                if (indirectSamples > 256) {
                    cout << "Processing may be a bit slow due to high number of paths" << endl;
                } else if (indirectSamples <= 0) {
                    cout << "Number of paths can not be negative, using default value = 128" << endl;
                    indirectSamples = 128;
                }
            }
        } else if (arguments.at(j) == "-i" || arguments.at(j) == "--info") {
            printUsage();
            return 0;
        } else if (arguments.at(j) == "-f" || arguments.at(j) == "--file") {
            ++j;
            fileName = "../images/" + arguments.at(j) + ".ppm";
        } else if (arguments.at(j) == "-w" || arguments.at(j) == "--width") {
            ++j;
            if (j > argc) {
                cout << "Using default width of image 720 pixels." << endl;
            } else {
                width = stoi(arguments.at(j));
                if (width <= 0) {
                    cout << "Width can not be negative, using default value = 720" << endl;
                    width = 720;
                }
            }
        } else if (arguments.at(j) == "-h" || arguments.at(j) == "--height") {
            ++j;
            if (j > argc) {
                cout << "Using default height of image 720 pixels." << endl;
            } else {
                height = stoi(arguments.at(j));
                if (height <= 0) {
                    cout << "Height can not be negative, using default value = 720" << endl;
                    height = 720;
                }
            }
        } else {
            cerr << arguments.at(j) << " could not be recognized as a supported argument. Check typo." << endl;
            printUsage();
            return -1;
        }
    }

    Scene scene = Scene(sceneStr, width, height);

    Tracer tracer = Tracer(fileName, scene);
    tracer.SAMPLES = indirectSamples;
    tracer.renderImageMultithread();

    return 0;
}

void printUsage() {
    cout << "Usage: render [-h | --help] [-s | --samples] [-of | --outfile]\n"
            "Options description:\n"
            "\t -s --samples <INTEGER>          : number of indirect samples rays, 128 if not specified.\n"
            "\t -f --file <STRING>              : path for the image to be saved (extension no need) e.g: /home/image \n"
            "\t -i --info                       : this message itself.\n"
            "\t -w --width <INTEGER>            : width of the image in pixels.\n"
            "\t -h --height                     : height of the image in pixels.\n" << endl;
}


string currentDate() {
    char buffer[80];
    time_t t = time(nullptr);   // get time now
    struct tm * now = localtime( & t );

    strftime(buffer,sizeof(buffer),"_%m_%d_%Y_%H:%M:%S", now);
    std::string str(buffer);
    return str;
}