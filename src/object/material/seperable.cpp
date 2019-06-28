#include <object/material/seperable.h>

SeperableBSSRDF::SeperableBSSRDF(const float &e, const float &r){
    EPS = e;
    rr = r;
}

void SeperableBSSRDF::sample_r(float &r, float &p, float &fr){
    r = (1.0f / (1.0f - drand48()) - 1.0f) * rr;
    p = 1.0f / ((r + 1.0f) * (r + 1.0f));
    fr = EPS * p;
}

void SeperableBSSRDF::sample_w(const Point &po , const Vector &wo, Vector &wi, float &p){
    Sampler *sampler = new UniformCosineSphereSampler();
    wi = Vector(sampler->sample().p3);
    p = wi.z();
}

void SeperableBSSRDF::sample_sp(const Normal &n){
    float u1 = drand48();
    Normal nn = n;
    Vector vx, vy, vz;
    if (u1 < 0.5f){
        vz = nn;
        nn.plateBase(vx, vy);
    }
    else if (u1 < 1.5f){
        vy = nn;
        nn.plateBase(vx, vz);
    }
    else{
        vx = nn;
        nn.plateBase(vz, vy);
    }

    float r = 2 * drand48() - 1.0f, phi = drand48() * 2.0f * PI;
    float rmax = 0.999f;
    if (r < 0.0f || r > rmax);
    float l = 2 * sqrt(rmax * rmax - r * r);

    Point p = r * (vx * cos(phi) + vy * sin(phi)) - l * vz * 0.5f;
    
}

void SeperableBSSRDF::sample_s(){

}