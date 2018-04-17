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
#include "Scene.h"
#include "Tracer.h"

void printUsage();

string currentDate();

using namespace std;

int main(int argc, char * argv[]){

    string fileScene, outfileName = "../images/image" + currentDate() + ".ppm";
    int indirectSamples = 128;//*10;

    vector<string> arguments;

    for (int i = 1; i < argc; ++i) {
        arguments.emplace_back(argv[i]);
    }

    for (unsigned long j = 0; j < arguments.size(); ++j) {
        if (arguments.at(j) == "-s" || arguments.at(j) == "--samples"){
            ++j;
            if (j > argc) {
                cout << "Using default indirect rays samples = 128" << endl;
            } else {
                indirectSamples = stoi(arguments.at(j));
                if (indirectSamples > 256) {
                    cout << "Processing may be a bit slow due to high number of samples" << endl;
                } else if (indirectSamples <= 0) {
                    cout << "Number of samples can not be negative, using default value = 128" << endl;
                    indirectSamples = 128;
                }
            }
        } else if (arguments.at(j) == "-h" || arguments.at(j) == "--help") {
            printUsage();
            return 0;
        } else if (arguments.at(j) == "-of" || arguments.at(j) == "--outfile") {
            ++j;
            outfileName = arguments.at(j) + ".ppm";
        } else {
            cerr << arguments.at(j) << " could not be recognized as a supported argument. Check typo." << endl;
            printUsage();
            return -1;
        }
    }

    Scene scene = Scene();

    Tracer tracer = Tracer(outfileName, scene);
    tracer.SAMPLES = indirectSamples;
    tracer.renderImageMultithread();

    return 0;
}

void printUsage() {
    cout << "Usage: render [-h | --help] [-s | --samples] [-of | --outfile]\n"
            "Options description:\n"
            "\t -s --samples <INTEGER>          : number of indirect samples rays, 128 if not specified.\n"
            "\t -of --outfile <STRING>          : path for the image to be saved (extension no need) e.g: /home/image.\n"
            "\t -h --help                       : this message itself.\n" << endl;
}

string currentDate() {
    char buffer[80];
    time_t t = time(nullptr);   // get time now
    struct tm * now = localtime( & t );

    strftime(buffer,sizeof(buffer),"_%d_%m_%Y_%I:%M:%S", now);
    std::string str(buffer);
    return str;
}

