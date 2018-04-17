/**
 *  @file    Tracer.cpp
 *  @authors Alfonso Delgado: 679745 at unizar dot es
 *           Álvaro Monteagudo: 681060 at unizar dot es
 *  @date    16/11/2017
 *  @version 1.0
 *
 *  @section DESCRIPTION
 *
 *  Implementation for tracer class
 */

#include <ctime>

#include "Tracer.h"
#include "samplingUtils.h"

using namespace std;

Tracer::Tracer(string filename, const Scene &scene) : scene(scene) {
    camera = this->scene.getCamera();
    shapes = this->scene.getShapes();
    totalPixels = camera.getHeight() * camera.getWidth();
    image = Image(camera.getWidth(), camera.getHeight());
    camera.calculateFirstPixel();
    outfileName = std::move(filename);

}


void printProgress(int numPixel, int total) {

    auto percentCompleted = static_cast<int>(numPixel / static_cast<float>(total) * 100.0f);

    cout << "Progress: [";

    for (int i = 0; i < round(percentCompleted / 2); ++i) {
        cout << "=";
    }

    if (total == numPixel) cout << "] 100%. ";
    else cout << "> " << percentCompleted << "%\r" << flush;
}

void Tracer::renderImage() const {

    Point pixel = camera.getFirstPixel();
    Point pixelRow = pixel;

    Dir colAdd(camera.getRight() * camera.getPixelSize());
    Dir rowAdd(camera.getUp() * camera.getPixelSize());

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < camera.getHeight(); ++i){
        for (int j = 0; j < camera.getWidth(); ++j) {
            printProgress(camera.getWidth() * i + j, totalPixels);

            Ray ray(camera.getFocal(), pixel);
            image(i,j) = radiance(ray);

            pixel = pixel + colAdd;
        }
        pixelRow = pixelRow - rowAdd;
        pixel = pixelRow;
    }

    printProgress(1, 1);

    auto end = std::chrono::high_resolution_clock::now();

    long elapsed_secs = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    long hours = elapsed_secs / 3600;
    long mins = elapsed_secs % 3600 / 60;
    long secs = elapsed_secs % 3600 % 60;

    cout << "Elapsed time: " << hours << " hours " << mins << " mins " << secs << " secs" << endl;

    image.saveImage(outfileName);
}

void Tracer::renderImageMultithread() const {
    //may return 0 when not able to detect
    int numThreads = std::thread::hardware_concurrency();

    if (numThreads == 0) {
        renderImage();
        return;
    }

    int linesPerThread = camera.getHeight() / numThreads;

    vector<thread> threads(static_cast<unsigned long>(numThreads));

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < numThreads; ++i) {
        int start = i*linesPerThread;
        int end = start + linesPerThread;
        if (i != numThreads - 1){
            threads[i] = thread(&Tracer::renderImageLines, this, start, end);
        } else {
            threads[i] = thread(&Tracer::renderImageLines, this, start, camera.getHeight());
        }
    }

    for (auto &thread : threads) {
        thread.join();
    }

    printProgress(1,1);

    auto end = std::chrono::high_resolution_clock::now();

    long elapsed_secs = std::chrono::duration_cast<std::chrono::seconds>(end - start_time).count();

    long hours = elapsed_secs / 3600;
    long mins = elapsed_secs % 3600 / 60;
    long secs = elapsed_secs % 3600 % 60;

    cout << "Elapsed time: " << hours << " hours " << mins << " mins " << secs << " secs" << endl;

    image.saveImage(outfileName);

}

void Tracer::renderImageLines(int start, int end) {

    Point pixel = camera.getFirstPixel();

    Dir colAdd(camera.getRight() * camera.getPixelSize());
    Dir rowAdd(camera.getUp() * camera.getPixelSize());

    // Update pixel position
    pixel = pixel - rowAdd * start;
    Point pixelRow = pixel;

    for (int i = start; i < end; ++i){
        for (int j = 0; j < image.getWidth(); ++j) {

            for (int k = 0; k < SAMPLES; ++k) {
                float randomWidthOffset, randomHeightOffset;
                randomRaySampling(randomWidthOffset, randomHeightOffset, camera.getPixelSize());
                Ray ray(camera.getFocal(),
                        Point(pixel.x + randomWidthOffset,
                              pixel.y + randomHeightOffset,
                              pixel.z));
                image(i,j) += radiance(ray);
            }
            image(i, j) /= SAMPLES;

            pixel = pixel + colAdd;

            if (start == 0) {
                printProgress(camera.getWidth() * i + j, camera.getWidth() * (end - start));
            }
        }
        pixelRow = pixelRow - rowAdd;
        pixel = pixelRow;
    }
}

inline bool Tracer::intersect(const Ray &ray, float &distance, int &id) const {
    float d;
    for (unsigned int i = 0; i < shapes.size(); ++i) {
        if ((d = shapes.at(static_cast<unsigned long>(i))->intersect(ray)) < distance) {
            distance = d;
            id = i;
        }
    }
    return distance < MAX_FLOAT;
}

RGB Tracer::radiance(const Ray &ray) const {

    float dist  = MAX_FLOAT;
    int id = -1;

    if (!intersect(ray, dist, id)) return BLACK;

    shared_ptr<Shape> shape = shapes.at(id);

    if (shape->getEmit() != BLACK) return shape->getEmit();

    // Getting intersection point coordinates
    Point intersectedPoint = ray.getSource() + (ray.getDirection() * dist);

    // Shape normal
    Dir normal = shape->getNormal(intersectedPoint).normalize();

    // Revert normal in order to work with the visible normal of the shape
    float cosi = normal.dot(ray.getDirection());
    Dir nl = ((cosi > 0) || (cosi == 0)) && (normal == ray.getDirection()) ? normal * -1 : normal;

    return russianRoulette(ray, *shape, intersectedPoint, nl);

}

RGB Tracer::russianRoulette(const Ray &ray, const Shape &shape, const Point &intersectedPoint, const Dir &normal) const {

    shared_ptr<Material> material = shape.getMaterial();

    float random = randomValue();

    float pd = material->getKd().getMean();
    float ps = material->getKs().getMean();
    float pr = material->getKr().getMean();
    float pt = material->getKt().getMean();

    if (random < pd) {

        Dir zAxis = shape.getNormal(intersectedPoint);
        Dir xAxis = (zAxis.x != 0) ? zAxis.cross(Dir(0, 0, 1)).normalize()
                                   : zAxis.cross(Dir(1, 0, 0)).normalize();
        Dir yAxis = xAxis.cross(zAxis);
        Mat transformToGlobalCoordinates = Mat(xAxis, yAxis, zAxis, intersectedPoint);

        // Uniform cosine
        float inclination, azimuth;
        std::tie(inclination, azimuth) = uniformCosineSampling();

        Dir rayDirLocal = Dir(sin(inclination) * cos(azimuth),
                              sin(inclination) * sin(azimuth),
                              cos(inclination));

        Ray sample(intersectedPoint, transformToGlobalCoordinates * rayDirLocal);

        return radiance(sample) * material->getKd() / pd;
    } else if (random < pd + ps) {

        Dir zAxis = shape.getNormal(intersectedPoint);
        Dir xAxis = (zAxis.x != 0) ? zAxis.cross(Dir(0, 0, 1)).normalize()
                                   : zAxis.cross(Dir(1, 0, 0)).normalize();
        Dir yAxis = xAxis.cross(zAxis);
        Mat transformToGlobalCoordinates = Mat(xAxis, yAxis, zAxis, intersectedPoint);

        // lobe specular
        float inclination, azimuth;
        std::tie(inclination, azimuth) = specularLobeSampling(shape.getShininess());

        Dir rayDirLocal = Dir(sin(inclination) * cos(azimuth),
                              sin(inclination) * sin(azimuth),
                              cos(inclination));

        Ray sample(intersectedPoint, transformToGlobalCoordinates * rayDirLocal);

        return radiance(sample) * material->getKs() *
               ((shape.getShininess() + 2.0f) /
                (shape.getShininess() + 1.0f)) / (pd + ps);
    } else if (random < pd + ps + pr) {
        if (material->getKr() != BLACK) {
            Ray reflectedRay(intersectedPoint, shape.getDirRayReflected(ray.getDirection(), normal));
            return radiance(reflectedRay) * material->getKr() / (pd + ps + pr);
        }
    } else if (random < pd + ps + pr + pt) {
        if (material->getKt() != BLACK) {
            Ray refractedRay(intersectedPoint, shape.getDirRayRefracted(ray.getDirection(), normal));
            return radiance(refractedRay) * material->getKt() / (pd + ps + pr + pt);
        }
    } else {
        return BLACK;
    }
}