#include <object/material/diffuse.h>

Diffuse::Diffuse(const Color &alb){
    albedo = alb;
}

float Diffuse::fr(const Vector &wi, const Vector &wo){
    return fmax(0.0f, wo.z() / wo.length());
}

void Diffuse::sample(const Vector &wi, Vector &wo, float &p, float &kf, Color &alb){
    // uniform cosine sphere sample
    Sampler *sample = new UniformCosineSphereSampler();
    wo = Vector(sample->sample().p3);
    wo.normalize();
    p = wo.z();
    kf = wo.z();
    alb = albedo;
}

Color Diffuse::color(const Color &Li){
    return Li.multi(albedo);
}

/*
* Diffuse Material is continuous
*/
bool Diffuse::isContinue(){
    return true;
}