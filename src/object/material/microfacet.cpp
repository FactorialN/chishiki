#include <object/material/microfacet.h>

Microfacet::Microfacet(const Color &Kd, const float &al){
    alpha = al;
    kd = Kd;
    ks = 1 - kd.max();
}

float Microfacet::Dc(const Vector &wh){
    float cosh = wh.z();
    float sinh = sqrt(1 - cosh * cosh);
    return exp(- sinh * sinh / (cosh * cosh * alpha * alpha)) / (cosh * cosh * cosh * alpha * alpha);
}

float Microfacet::Gc(const Vector &wv, const Vector &wh){
    float cosv = wv.z();
    float sinv = sqrt(1 - cosv * cosv);
    float b = cosv / (alpha * sinv);
    float secp = b < 1.6 ? (3.535f * b + 2.181f * b * b) / (1 + 2.276f * b + 2.577f * b * b) : 1.0f;
    float firp = (wv * wh) / cosv <= 0 ? 0 : 1;
    return firp * secp;
}

float Microfacet::fr(const Vector &wi, const Vector &wo){
    if (wi.z() > 0 || wo.z() <= 0) return 0.0f;
    Vector wh = (wo - wi);
    wh.normalize();
    float fr = ks * Dc(wh);
    float etaict = 1.0f / 1.5f;
    float costhetai = fabs(wi.z() / wi.length()), sinthetai = sqrt(1 - costhetai * costhetai);
    float sinthetat = etaict * sinthetai, costhetat = sqrt(1 - sinthetat * sinthetat);
    float rp = (costhetai - etaict * costhetat) / (costhetai + etaict * costhetat);
    float ro = (etaict * costhetai - costhetat) / (etaict * costhetai + costhetat);
    float ffr = 0.5f * (rp * rp + ro * ro);
    if (sinthetat > 1.0f) ffr = 1.0f;
    fr *= ffr;
    fr *= Gc(-1.0f * wi, wh) * Gc(wo, wh);
    fr /= 4.0f * (-wi.z()) * wo.z() * wh.z();
    fr += 1.0f / M_PI;
    return fr;
}

void Microfacet::sample(const Vector &wi, Vector &wo, float &p, float &kf, Color &alb){
    if (drand48() < ks){
        BeckmannSampler *sampler = new BeckmannSampler();
        Vector wn = sampler->sample(alpha).p3;
        wo = wi - 2 * wn * (wi * wn);
        wo.normalize();
        p = ks * sampler->pdf(alpha, wn);
        kf = fr(wi, wo) * wo.z();
        alb = Color(0.97f, 0.97f, 0.97f);
        delete sampler;
    }
    else{
        Sampler *sampler = new UniformCosineSphereSampler();
        wo = sampler->sample().p3;
        wo.normalize();
        p = (1.0f - ks) * wo.z();
        kf = wo.z();
        alb = kd;
    }
}

Color Microfacet::color(const Color &Li){
    return kd.multi(Li);
}

/*
* Microfacet Material is continuous
*/
bool Microfacet::isContinue(){
    return true;
}