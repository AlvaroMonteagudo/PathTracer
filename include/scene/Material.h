#pragma once

#include <RGB.h>
#include <memory>

using namespace std;

class Material {

public:

    Material(const RGB &kd, const RGB &ks, const RGB &kr, const RGB &kt);

    const RGB &getKd() const;

    const RGB &getKs() const;

    const RGB &getKr() const;

    const RGB &getKt() const;



private:

    RGB kd, ks, kr, kt;
};

static const shared_ptr<Material> MIRROR = make_shared<Material>(Material(BLACK, BLACK, WHITE, BLACK));
static const shared_ptr<Material> TRANSP = make_shared<Material>(Material(BLACK, BLACK, BLACK, WHITE));
static const shared_ptr<Material> DIFF_R = make_shared<Material>(Material(RED, BLACK, BLACK, BLACK));
static const shared_ptr<Material> DIFF_G = make_shared<Material>(Material(GREEN, BLACK, BLACK, BLACK));
static const shared_ptr<Material> DIFF_B = make_shared<Material>(Material(BLUE, BLACK, BLACK, BLACK));
static const shared_ptr<Material> LAMBERTIAN = make_shared<Material>(Material(WHITE, BLACK, BLACK , BLACK));
