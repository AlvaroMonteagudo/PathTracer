#include <Material.h>

Material::Material(const RGB &kd, const RGB &ks, const RGB &kr, const RGB &kt)
        : kd(kd), ks(ks), kr(kr), kt(kt) {}


const RGB &Material::getKd() const {
    return kd;
}

const RGB &Material::getKs() const {
    return ks;
}

const RGB &Material::getKr() const {
    return kr;
}

const RGB &Material::getKt() const {
    return kt;
}

