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

static map<string, tuple<int, int>> resolutions;


int main(int argc, char * argv[]){


    string sceneStr = "cornell", fileName = "../images/image" + currentDate() + ".ppm";
    int paths = 64, width = 720, height = 720, depth = 5;
    bool nee = false;


    resolutions["240"] = std::make_tuple(352, 240);
    resolutions["360"] = std::make_tuple(480, 360);
    resolutions["480"] = std::make_tuple(858, 480);
    resolutions["720"] = std::make_tuple(1280, 720);
    resolutions["1080"] = std::make_tuple(1920, 1080);

    vector<string> arguments;


    for (int i = 1; i < argc; ++i) {
        arguments.emplace_back(argv[i]);
    }

    for (unsigned long j = 0; j < arguments.size(); ++j) {
        if (arguments.at(j) == "-s" || arguments.at(j) == "--scene") {
            ++j;
            sceneStr = arguments.at(j);
        } else if (arguments.at(j) == "-p" || arguments.at(j) == "--paths"){
            ++j;
            if (j > argc) {
                cout << "Using default number of paths = 128, number not provided." << endl;
            } else {
                paths = stoi(arguments.at(j));
                if (paths > 256) {
                    cout << "Processing may be a bit slow due to high number of paths" << endl;
                } else if (paths <= 0) {
                    cout << "Number of paths can not be negative, using default value = 32" << endl;
                    paths = 32;
                }
            }
        } else if (arguments.at(j) == "-d" || arguments.at(j) == "--depth"){
            ++j;
            if (j > argc) {
                cout << "Using default max depth = 5, number not provided." << endl;
            } else {
                depth = stoi(arguments.at(j));
                if (depth <= 0) {
                    cout << "Max depth can not be negative, using default value = 5" << endl;
                    depth = 5;
                }
            }
        }else if (arguments.at(j) == "-i" || arguments.at(j) == "--info") {
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
        } else if (arguments.at(j) == "-res" || arguments.at(j) == "--resolution") {
            ++j;
            string resolution = arguments.at(j);
            if (resolutions.find(resolution) != resolutions.end()) {
                auto res = resolutions[resolution];
                width = get<0>(res);
                height = get<1>(res);
            } else {
                cout << "Unknown resolution. Try one of these: 240, 360, 480, 720 and 1080." << endl;
            }


        } else if (arguments.at(j) == "-nee") {
            nee = true;
        } else {
            cerr << arguments.at(j) << " could not be recognized as a supported argument. Check typo." << endl;
            printUsage();
            return 0;
        }
    }

    Scene scene = Scene(sceneStr, width, height);

    Tracer tracer = Tracer(fileName, scene);
    tracer.SAMPLES = paths;
    tracer.NEE = nee;
    tracer.MAX_DEPTH = depth;
    tracer.renderImageMultithread();

    return 0;
}

void printUsage() {
    cout << "Usage: render [-h | --help] [-s | --samples] [-of | --outfile]\n"
            "Options description:\n"
            "\t -p --paths <INTEGER> : number of indirect samples rays, 32 if not specified.\n"
            "\t -d --depth <INTEGER> : Max depth of exploration for the algorithm, 5 if not specified.\n"
            "\t -f --file <STRING>   : path for the image to be saved (extension no need) e.g: /home/image \n"
            "\t -i --info            : this message itself.\n"
            "\t -w --width <INTEGER> : width of the image in pixels.\n"
            "\t -h --height          : height of the image in pixels.\n"
            "\t -s --scene <STRING>  : height of the image in pixels.\n" << endl;
}


string currentDate() {
    char buffer[80];
    time_t t = time(nullptr);   // get time now
    struct tm * now = localtime( & t );

    strftime(buffer,sizeof(buffer),"_%m_%d_%Y_%H:%M:%S", now);
    std::string str(buffer);
    return str;
}