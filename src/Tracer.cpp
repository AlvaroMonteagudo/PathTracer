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


Tracer::Tracer(string filename) : scene(Scene()) {
    camera = scene.getCamera();
    shapes = scene.getShapes();
    lights = scene.getLights();
    areaLights = scene.getAreaLights();
    totalPixels = camera.getHeight() * camera.getWidth();
    image = Image(camera.getWidth(), camera.getHeight());
    camera.calculateFirstPixel();
    outfileName = std::move(filename);
}

Tracer::Tracer(string filename, const Scene &scene) : scene(scene) {
    camera = this->scene.getCamera();
    shapes = this->scene.getShapes();
    lights = this->scene.getLights();
    areaLights = this->scene.getAreaLights();
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
            image(i,j) = radiance(ray, 0);

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

    vector<thread> threads(numThreads);

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
                image(i,j) += radiance(ray, 0);
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
    for (int i = 0; i < shapes.size(); ++i) {
        if ((d = shapes.at(i)->intersect(ray)) < distance) {
            distance = d;
            id = i;
        }
    }
    return distance < MAX_FLOAT;
}

/*RGB Tracer::radiance(const Ray &ray, int depth) const {

    RGB acumColor = BLACK, acumRefl = WHITE;

    float dist  = MAX_FLOAT;
    int id = -1;

    Ray _ray = ray;

    while (1){
        if (++depth == MAX_DEPTH) return acumColor;

        if (!intersect(_ray, dist, id)) return acumColor;

        const shared_ptr<Shape> shape = shapes.at(id);

        if (shape->getEmit() != BLACK) return acumColor * shape->getEmit();

        Point intersectedPoint = ray.getSource() + (ray.getDirection() * dist);
        Dir normal = shape->getNormal(intersectedPoint).normalize();

        float random = randomValue();

        if (random < shape->getKd().getMean()) {

            Dir zAxis = shape->getNormal(intersectedPoint);
            Dir xAxis = ((zAxis.x != 0) ? Dir(0, 1, 0) : Dir(1, 0, 0)).cross(zAxis).normalize();
            Dir yAxis = zAxis.cross(xAxis);
            Mat transformToGlobalCoordinates = Mat(xAxis, yAxis, zAxis, intersectedPoint);

            // Uniform cosine
            float inclination, azimuth;
            uniformCosineSampling(inclination, azimuth);

            Dir rayDirLocal = Dir(sin(inclination) * cos(azimuth),
                                  sin(inclination) * sin(azimuth),
                                  cos(inclination));

            Ray sample(intersectedPoint, transformToGlobalCoordinates * rayDirLocal);
            RGB phong = shape->phong(ray, Ray(sample.getSource(), sample.getDirection() * -1), intersectedPoint);

            acumColor += acumRefl * phong;
            acumRefl *= phong;

            _ray = sample;
            continue;
        }

    }


    /*else if (random < shape->getKd().getMean() + shape->getKs().getMean()) {

        Dir zAxis = shape->getNormal(intersectedPoint);
        Dir xAxis = ((zAxis.x != 0) ? Dir(0, 1, 0) : Dir(1, 0, 0)).cross(zAxis).normalize();
        Dir yAxis = zAxis.cross(xAxis);
        Mat transformToGlobalCoordinates = Mat(xAxis, yAxis, zAxis, intersectedPoint);

        // lobe specular
        float inclination, azimuth;
        specularLobeSampling(inclination, azimuth, shape->getShininess());

        Dir rayDirLocal = Dir(sin(inclination) * cos(azimuth),
                              sin(inclination) * sin(azimuth),
                              cos(inclination));

        Dir rayDir = transformToGlobalCoordinates * rayDirLocal; // Get global coordinates ray direction

        Ray sample(intersectedPoint, rayDir);

        return radiance(sample, depth) * shape->getKs() *
               (shape->getShininess() + 2.0f) /
               (shape->getShininess() + 1.0f);
    } else {
        /*if (shape->getKr() != BLACK) {
            Ray reflectedRay(intersectedPoint, shape->getDirRayReflected(ray.getDirection(), nl));
            return radiance(reflectedRay, depth) * shape->getKr();
        }

        if (shape->getKt() != BLACK) {
            Ray refractedRay(intersectedPoint, shape->getDirRayRefracted(ray.getDirection(), nl));
            return radiance(refractedRay, depth) * shape->getKt();
        };*/
        //return BLACK;
    //}*/
//}*/

RGB Tracer::radiance(const Ray &ray, int depth) const {

    float dist  = MAX_FLOAT;
    int id = -1;

    if (!intersect(ray, dist, id)) return BLACK;

    const shared_ptr<Shape> shape = shapes.at(id);

    if (shape->getEmit() != BLACK) return shape->getEmit();

    Point intersectedPoint = ray.getSource() + (ray.getDirection() * dist);
    Dir normal = shape->getNormal(intersectedPoint).normalize();
    Dir nl = (normal.dot(ray.getDirection()) < 0) ? normal : normal * -1;

    float random = randomValue();

    if (random < shape->getKd().getMean()) {

        Dir zAxis = shape->getNormal(intersectedPoint);
        Dir xAxis = ((zAxis.x != 0) ? Dir(0, 1, 0) : Dir(1, 0, 0)).cross(zAxis).normalize();
        Dir yAxis = zAxis.cross(xAxis);
        Mat transformToGlobalCoordinates = Mat(xAxis, yAxis, zAxis, intersectedPoint);

        // Uniform cosine
        float inclination, azimuth;
        uniformCosineSampling(inclination, azimuth);

        Dir rayDirLocal = Dir(sin(inclination) * cos(azimuth),
                              sin(inclination) * sin(azimuth),
                              cos(inclination));

        Ray sample(intersectedPoint, transformToGlobalCoordinates * rayDirLocal);

        return radiance(sample, depth) * shape->getKd();
        //return shape->getEmit() + shape->phong(ray, sample, intersectedPoint) * radiance(sample, depth);
    } else if (random < shape->getKd().getMean() + shape->getKs().getMean()) {

        Dir zAxis = shape->getNormal(intersectedPoint);
        Dir xAxis = ((zAxis.x != 0) ? Dir(0, 1, 0) : Dir(1, 0, 0)).cross(zAxis).normalize();
        Dir yAxis = zAxis.cross(xAxis);
        Mat transformToGlobalCoordinates = Mat(xAxis, yAxis, zAxis, intersectedPoint);

        // lobe specular
        float inclination, azimuth;
        specularLobeSampling(inclination, azimuth, shape->getShininess());

        Dir rayDirLocal = Dir(sin(inclination) * cos(azimuth),
                              sin(inclination) * sin(azimuth),
                              cos(inclination));

        Dir rayDir = transformToGlobalCoordinates * rayDirLocal; // Get global coordinates ray direction

        Ray sample(intersectedPoint, rayDir);

        return radiance(sample, depth) * shape->getKs() *
               (shape->getShininess() + 2.0f) /
               (shape->getShininess() + 1.0f);
    } else if (random < (shape->getKd().getMean() +
                         shape->getKs().getMean() +
                         shape->getKr().getMean())) {
        if (shape->getKr() != BLACK) {
            Ray reflectedRay(intersectedPoint, shape->getDirRayReflected(ray.getDirection(), nl));
            return radiance(reflectedRay, depth) * shape->getKr();
        }
    } else if (random < (shape->getKd().getMean() +
                         shape->getKs().getMean() +
                         shape->getKr().getMean() +
                         shape->getKt().getMean())) {
        if (shape->getKt() != BLACK) {
            Ray refractedRay(intersectedPoint, shape->getDirRayRefracted(ray.getDirection(), nl));
            return radiance(refractedRay, depth) * shape->getKt();
        }
    } else {
        return BLACK;
    }
}

RGB Tracer::directLight(const Point &intersectedPoint, const Dir &normal,
                        const shared_ptr<Shape> &shape, const Ray &ray) const {

    RGB color = BLACK;

    for (LightSource light : lights) {

        bool inShadow = false;
        Ray shadow = Ray(light.getPoint(), intersectedPoint);
        float lightDist = (shadow.getSource() - intersectedPoint).module();

        for (const shared_ptr<Shape> &item : shapes) {

            float disShape = item->intersect(shadow);

            if (disShape + THRESHOLD <= lightDist && item->getKt() == BLACK) {
                inShadow = true;
                break;
            }
        }

        if(!inShadow) {
            float cos = shadow.getDirection().dot(normal);
            //color += (Phong(Ray(ray.getSource(), ray.getDirection() * -1), shadow, normal, shape, intersectedPoint)
             //         * (light.getIntensity() / (lightDist * lightDist)) * std::abs(cos));

        }
    }

    return color;
}

RGB Tracer::indirectLight(const Point &intersectedPoint, const Dir &normalShape, shared_ptr<Shape> &shape,
                          const Ray &ray, int depth) const {

    RGB result = BLACK;

    Dir xAxis;
    Dir zAxis = normalShape;

    if(zAxis.x != 0) {
        xAxis = zAxis.cross(Dir(0, 0, 1)).normalize();
    } else {
        xAxis = zAxis.cross(Dir(1, 0, 0)).normalize();
    }
    Dir yAxis = xAxis.cross(zAxis);

    Mat transformToGlobalCoordinates = Mat(xAxis, yAxis, zAxis, intersectedPoint);

    for (int i = 0; i < SAMPLES; ++i) {

        float inclination, azimuth;
        uniformCosineSampling(inclination, azimuth);

        Dir rayDirLocal = Dir(sin(inclination) * cos(azimuth),
                              sin(inclination) * sin(azimuth),
                              cos(inclination));

        Dir rayDir = transformToGlobalCoordinates * rayDirLocal; // Get global coordinates ray direction

        Ray sample(intersectedPoint, rayDir);

        /*result += radiance(sample, depth + 1, indirectSteps + 1) *
                  Phong(Ray(ray.getSource(), ray.getDirection() * -1), sample,
                        normalShape, shape, intersectedPoint) * PI;*/
    }

    return result / SAMPLES;

}

RGB Tracer::deltaInteraction(const Point &intersectedPoint, const Dir &normal,
                             const shared_ptr<Shape> &shape, const Ray &ray, int depth, int indirectSteps) const {
    RGB color = BLACK;

    if (depth >= MAX_DEPTH) return color;

    if (shape->getKr() != BLACK) {
        Ray reflectedRay(intersectedPoint, shape->getDirRayReflected(ray.getDirection(), normal));
        //color += radiance(reflectedRay, depth + 1, indirectSteps) * shape->getKr();
    }

    if (shape->getKt() != BLACK) {
        //Ray refractedRay(intersectedPoint, shape->getDirRayRefracted(ray.getDirection(), normal * -1));
        //color += radiance(refractedRay, depth + 1, indirectSteps) * shape->getKt();
    }

    return color;
}


RGB Tracer::RussianRoulette(const Point &intersectedPoint, const shared_ptr<Shape> shape, int depth) const {

    float random = randomValue();

    Dir xAxis;
    Dir zAxis = shape->getNormal(intersectedPoint);

    if(zAxis.x != 0) {
        xAxis = zAxis.cross(Dir(0, 0, 1)).normalize();
    } else {
        xAxis = zAxis.cross(Dir(1, 0, 0)).normalize();
    }
    Dir yAxis = xAxis.cross(zAxis);

    Mat transformToGlobalCoordinates = Mat(xAxis, yAxis, zAxis, intersectedPoint);

    if (random < shape->getKd().getMax()) {
        // Uniform cosine
        float inclination, azimuth;
        uniformCosineSampling(inclination, azimuth);

        Dir rayDirLocal = Dir(sin(inclination) * cos(azimuth),
                              sin(inclination) * sin(azimuth),
                              cos(inclination));

        Dir rayDir = transformToGlobalCoordinates * rayDirLocal; // Get global coordinates ray direction

        Ray sample(intersectedPoint, rayDir);

        return radiance(sample, depth + 1) * shape->getKd(); // PI sin and cos cancelled with pdf product

    } else if (random < shape->getKd().getMax() + shape->getKs().getMean()) {
        // lobe specular
        float inclination, azimuth;
        specularLobeSampling(inclination, azimuth, shape->getShininess());

        Dir rayDirLocal = Dir(sin(inclination) * cos(azimuth),
                              sin(inclination) * sin(azimuth),
                              cos(inclination));

        Dir rayDir = transformToGlobalCoordinates * rayDirLocal; // Get global coordinates ray direction

        Ray sample(intersectedPoint, rayDir);

        return radiance(sample, depth + 1) * shape->getKs() *
                (shape->getShininess() + 2.0f) /
                (shape->getShininess() + 1.0f);
    } else {
        return BLACK;
    }

}




