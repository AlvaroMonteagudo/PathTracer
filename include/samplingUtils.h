#pragma once

float randomValue() {
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0, 1);
    return distribution(generator);
}


void uniformCosineSampling(float &inclination, float &azimuth){
    inclination = acos(sqrt(1 - randomValue()));
    azimuth = 2.0f * PI * randomValue();
}

void specularLobeSampling(float &inclination, float &azimuth, float alpha){
    inclination = acos(pow(randomValue(), (1 /(alpha + 1))));
    azimuth = 2.0f * PI * randomValue();
}

void randomRaySampling(float &widthOffset, float &heightOffset, float pixelSize){
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0, pixelSize);

    widthOffset = distribution(generator) - pixelSize / 2.0f;
    heightOffset = distribution(generator) - pixelSize / 2.0f;
}

