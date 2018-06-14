#pragma once

#include <cmath>
#include <limits>

#define THRESHOLD 0.0001
#define MIN_FLOAT std::numeric_limits<float>::min()
#define MAX_FLOAT std::numeric_limits<float>::max()
#define EPSILON   std::numeric_limits<float>::epsilon()

static float solveQuadratic(float a, float b, float c) {

    float discriminant = b*b - 4*a*c;

    // Abort if less than 0
    if (discriminant < 0.0) {
        return MAX_FLOAT;
    } else if (discriminant > 0.0) {
        auto x1 = static_cast<float>((-b - sqrtf(discriminant)) / (2.0f * a));
        auto x2 = static_cast<float>((-b + sqrtf(discriminant)) / (2.0f * a));

        if ((x1 > THRESHOLD) && ((x1 < x2) || (x2 <= THRESHOLD))) {
            return x1;
        } else if ((x2 > THRESHOLD) && ((x2 < x1) || (x1 <= THRESHOLD))) {
            return x2;
        } else {
            return MAX_FLOAT;
        }
    } else {
        float x = -b / (2.0f * a);
        return x > THRESHOLD ? x : MAX_FLOAT;
    }
}
