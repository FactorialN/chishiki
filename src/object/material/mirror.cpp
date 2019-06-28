#include <object/material/mirror.h>

Mirror::Mirror(const Color &alb){
    albedo = alb;
}

float Mirror::fr(const Vector &wi, const Vector &wo){
    Vector w;
    float p, kf;
    Color alb;
    sample(wi, w, p, kf, alb);
    if (w * wo + eps > 1.0f) return kf;
    return 0.0f;
}

void Mirror::sample(const Vector &wi, Vector &wo, float &p, float &kf, Color &alb){
    p = 1.0f;
    wo = Vector(wi.x(), wi.y(), -wi.z());
    wo.normalize();
    kf = 1.0f;
    alb = albedo;
}

Color Mirror::color(const Color &Li){
    return albedo.multi(Li);
}

/*
* Mirror Material is not continuous
*/
bool Mirror::isContinue(){
    return false;
}