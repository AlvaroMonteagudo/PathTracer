#include <Material.h>
#include <iostream>

Material::Material(const RGB &d, const RGB &s, const RGB &r, const RGB &t, float shininess) :
        kd(d), ks(s), kr(r), kt(t), shininess(shininess) {
    float max = 0;
    if ((max = d.getRed() + s.getRed() + r.getRed() + t.getRed()) > 0.95f) {
        cout << "Red color exceed maximum conservative value 0.95. It will be readjusted proportionally to satisfy the limit established." << endl;
        kd.setRed(d.getRed() / max * 0.9f);
        ks.setRed(s.getRed() / max * 0.9f);
        kr.setRed(r.getRed() / max * 0.9f);
        kt.setRed(t.getRed() / max * 0.9f);
    }

    if ((max = d.getBlue() + s.getBlue() + r.getBlue() + t.getBlue()) > 0.95f) {
        cout << "Blue color exceed maximum conservative value 0.95. It will be readjusted proportionally to satisfy the limit established." << endl;
        kd.setBlue(d.getBlue() / max * 0.9f);
        ks.setBlue(s.getBlue() / max * 0.9f);
        kr.setBlue(r.getBlue() / max * 0.9f);
        kt.setBlue(t.getBlue() / max * 0.9f);
    }

    if ((max = d.getGreen() + s.getGreen() + r.getRed() + t.getRed()) > 0.95f) {
        cout << "Green color exceed maximum conservative value 0.95. It will be readjusted proportionally to satisfy the limit established." << endl;
        kd.setGreen(d.getGreen() / max * 0.9f);
        ks.setGreen(s.getGreen() / max * 0.9f);
        kr.setGreen(r.getGreen() / max * 0.9f);
        kt.setGreen(t.getGreen() / max * 0.9f);
    }
}


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

float Material::getShininess() const {
    return shininess;
}

Material Material::operator + (const Material &m) const {
    return { kd + m.getKd(), ks + m.getKs(), kr + m.getKr(), kt + m.getKt(), shininess + m.getShininess() };
}