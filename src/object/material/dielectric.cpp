#include <object/material/dielectric.h>

Dielectric::Dielectric(const Color &alb, const float &e){
    albedo = alb;
    eta = e;
}

/*
* Calculate the possiblity of sampling wo
*/
float Dielectric::fr(const Vector &wi, const Vector &wo){
    float etaict = wi.z() < 0.0f ? 1.0f / eta : eta;
    float costhetai = fabs(wi.z() / wi.length()), sinthetai = sqrt(1 - costhetai * costhetai);
    float sinthetat = etaict * sinthetai, costhetat = sqrt(1 - sinthetat * sinthetat);
    float rp = (costhetai - etaict * costhetat) / (costhetai + etaict * costhetat);
    float ro = (etaict * costhetai - costhetat) / (etaict * costhetai + costhetat);
    float fr = 0.5f * (rp * rp + ro * ro);
    if (sinthetat > 1) fr = 1.0f;
    Vector w1 = Vector(wi.x(), wi.y(), -wi.z());
    float xp = wi.x() / sqrt(wi.x() * wi.x() + wi.y() * wi.y());
    float yp = wi.y() / sqrt(wi.y() * wi.y() + wi.x() * wi.x());
    Vector w2 = Vector(sinthetat * xp, sinthetat * yp, wi.z() > 0.0f ? costhetat : -costhetat);
    if (wo * w1 + eps > 1.0f) return fr;
    else if(sinthetat < 1.0f && wo * w2 + eps > 1.0f) return 1.0f - fr;
    return 0.0f;
}

/*
* sample an output ray
*/
void Dielectric::sample(const Vector &wi, Vector &wo, float &p, float &kf, Color &alb){
    float etaict = wi.z() < 0.0f ? 1.0f / eta : eta;
    float costhetai = fabs(wi.z() / wi.length()), sinthetai = sqrt(1 - costhetai * costhetai);
    float sinthetat = etaict * sinthetai, costhetat = sqrt(1 - sinthetat * sinthetat);
    float rp = (costhetai - etaict * costhetat) / (costhetai + etaict * costhetat);
    float ro = (etaict * costhetai - costhetat) / (etaict * costhetai + costhetat);
    float fr = 0.5f * (rp * rp + ro * ro);
    if (sinthetat > 1.0f) fr = 1.0f;
    if (drand48() < fr){
        // reflection
        p = fr;
        kf = fr;
        wo = Vector(wi.x(), wi.y(), -wi.z());
        wo.normalize();
    }
    else{
        // refraction
        p = 1.0f - fr;
        kf = 1.0f - fr;
        float xp = wi.x() / sqrt(wi.x() * wi.x() + wi.y() * wi.y());
        float yp = wi.y() / sqrt(wi.y() * wi.y() + wi.x() * wi.x());
        wo = Vector(sinthetat * xp, sinthetat * yp, wi.z() > 0.0f ? costhetat : -costhetat);
        wo.normalize();
    }
    alb = albedo;
}

/*
* calculate output color
*/
Color Dielectric::color(const Color &Li){
    return albedo.multi(Li);
}

/*
* Dielectric Material is not continuous
*/
bool Dielectric::isContinue(){
    return false;
}