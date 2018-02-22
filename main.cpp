/**
 *  @file    Sphere.h
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

void printFormat();

string currentDate();

using namespace std;

int main(int argc, char * argv[]){

    string fileScene, outfileName = "../images/image" + currentDate() + ".ppm";
    int indirectSamples = 32;
    int indirectSteps = 1;
    int rayTraceDepth = 5;

    vector<string> arguments;

    for (int i = 1; i < argc; ++i) {
        arguments.emplace_back(argv[i]);
    }

    for (unsigned long j = 0; j < arguments.size(); ++j) {
        if (arguments.at(j) == "-f" || arguments.at(j) == "--file") {
            ++j;
            if (j > argc) {
                cerr << "You have to specified a valid file path" << endl;
                return -1;
            }
            ifstream file(arguments.at(j).c_str());
            if (file.good()) {
                fileScene = arguments.at(j);
            } else {
                cerr << "Could not find specified file. Make sure it match the path to it." << endl;
                return -1;
            }
        } else if (arguments.at(j) == "-s" || arguments.at(j) == "--samples"){
            ++j;
            if (j > argc) {
                cout << "Using default indirect rays samples = 128" << endl;
            } else {
                indirectSamples = stoi(arguments.at(j));
                if (indirectSamples > 256) {
                    cout << "Processing may be a bit slow due to high number of samples" << endl;
                } else if (indirectSamples < 0) {
                    cout << "Number of samples can not be negative, using default value = 128" << endl;
                    indirectSamples = 128;
                }
            }
        } else if (arguments.at(j) == "-i" || arguments.at(j) == "--indirect_steps"){
            ++j;
            if (j > argc) {
                cout << "Using default indirect steps = 1" << endl;
            } else {
                indirectSteps = stoi(arguments.at(j));
                //cout << "Take into account that indirect steps increments time exponentially, you have not infinite time to wait." << endl;
                if (indirectSteps < 0) {
                    cout << "Number of indirect steps can not be negative, using default value = 128" << endl;
                    indirectSteps = 128;
                }
            }
        } else if (arguments.at(j) == "-d" || arguments.at(j) == "--depth") {
            ++j;
            if (j > argc) {
                cout << "Using default depth for path trace = 5" << endl;
            } else {
                rayTraceDepth = stoi(arguments.at(j));
                if (indirectSamples < 0) {
                    cout << "Number of path trace depth can not be negative, using default value = 5" << endl;
                    rayTraceDepth = 5;
                }
            }
        } else if (arguments.at(j) == "-FORMAT") {
            printFormat();
            return 0;
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
    tracer.MAX_INDIRECT_STEPS = indirectSteps;
    tracer.MAX_DEPTH = rayTraceDepth;
    tracer.SAMPLES = indirectSamples;
    tracer.renderImageMultithread();

    return 0;
}

void printFormat() {
    cout << "Some technical description to set scenes within a file.\n"
            "Comments available with # at the start of the line.\n"
            "Item description using similar format to yaml:\n"
            "\t - Available items: Plane and Sphere.\n"
            "\t - Key-value system\n"
            "\t - The following example shows all compulsory attributes. Optional attribute: shininess.\n"
            "e.g. formatted file:\n"
            "\t# Plane\n"
            "\tPlane {\n"
            "\t\tPoint: 0 0 1.5\n"
            "\t\tNormal: -0.8 0 -1\n"
            "\t\tMaterial {\n"
            "\t\t\tDiffuse: 127 127 127\n"
            "\t\t\tSpecular: 0 0 0\n"
            "\t\t\tReflectance: 0 0 0\n"
            "\t\t\tTransmittance: 0 0 0\n"
            "\t\t}\n"
            "\t}\n"
            "\t# Sphere\n"
            "\tSphere {\n"
            "\t\tPoint: 0 -0.7 -0.2\n"
            "\t\tRadius: 0.3\n"
            "\t\tMaterial {\n"
            "\t\t\tDiffuse: 255 0 0\n"
            "\t\t\tSpecular: 0 0 0\n"
            "\t\t\tReflectance: 0 0 0\n"
            "\t\t\tTransmittance: 0 0 0\n"
            "\t\t}\n"
            "\t}\n" << endl;

}

void printUsage() {
    cout << "Usage: render [-h | --help]  [-f | --file]  [-s | --samples]  [-d | --depth]\n"
            "Options description:\n"
            "\t -d --depth <INTEGER>            : depth of path trace, 5 if not specified.\n"
            "\t -s --samples <INTEGER>          : number of indirect samples rays, 128 if not specified.\n"
            "\t -i --indirect_steps <INTEGER>   : number of indirect steps, 1 by default.\n"
            "\t -of --outfile <STRING>          : path for the image to be saved (extension no need) e.g: /home/image.\n"
            "\t -f --file <STRING>              : file that contains described scene to render, cornell box will be rendered if not specified.\n"
            "\t -FORMAT                         : print useful description about format supported.\n"
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

