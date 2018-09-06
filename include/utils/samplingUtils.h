#pragma once

#include <random>

inline static float randomValue() {
    static random_device device;
    static mt19937 mt(device());
    static uniform_real_distribution<float> distribution(0, 1);
    return distribution(mt);
}


std::tuple<float, float> uniformCosineSampling(){
    float inclination = acos(sqrt(1 - randomValue()));
    float azimuth = 2.0f * PI * randomValue();
    return std::make_tuple(inclination, azimuth);
}

std::tuple<float, float> specularLobeSampling(float alpha){
    float inclination = acos(pow(randomValue(), (1 /(alpha + 1))));
    float azimuth = 2.0f * PI * randomValue();
    return std::make_tuple(inclination, azimuth);
}

void randomRaySampling(float &widthOffset, float &heightOffset, float pixelSize){
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0, pixelSize);

    widthOffset = distribution(generator) - pixelSize / 2.0f;
    heightOffset = distribution(generator) - pixelSize / 2.0f;
}

