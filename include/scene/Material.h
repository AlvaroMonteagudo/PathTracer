#pragma once

#include <RGB.h>
#include <memory>

using namespace std;

class Material {

public:

    Material(const RGB &kd, const RGB &ks, const RGB &kr, const RGB &kt, float shininess = 0.0f);

    const RGB &getKd() const;

    const RGB &getKs() const;

    const RGB &getKr() const;

    const RGB &getKt() const;

    float getShininess() const;

    Material operator + (const Material &m) const;

private:

    RGB kd, ks, kr, kt;

    float shininess;
};

inline Material Diffuse(const RGB &color) {
    return { color, BLACK, BLACK, BLACK };
}

inline Material Specular(const RGB &color, float shininess) {
    return { BLACK, color, BLACK, BLACK, shininess };
}

inline Material Reflective(const RGB &color) {
    return { BLACK, BLACK, color, BLACK };
}

inline Material Transmittive(const RGB &color) {
    return { BLACK, BLACK, BLACK, color };
}


static const shared_ptr<Material> MIRROR = make_shared<Material>(Material(BLACK, BLACK, WHITE, BLACK));
static const shared_ptr<Material> TRANSP = make_shared<Material>(Material(BLACK, BLACK, BLACK, WHITE));
static const shared_ptr<Material> DIFF_R = make_shared<Material>(Material(RED, BLACK, BLACK, BLACK));
static const shared_ptr<Material> DIFF_G = make_shared<Material>(Material(GREEN, BLACK, BLACK, BLACK));
static const shared_ptr<Material> DIFF_B = make_shared<Material>(Material(BLUE, BLACK, BLACK, BLACK));
static const shared_ptr<Material> LAMBERTIAN = make_shared<Material>(Material(WHITE / 2, BLACK, BLACK , BLACK));
