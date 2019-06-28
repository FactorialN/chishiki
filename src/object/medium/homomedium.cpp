#include <object/medium/homomedium.h>

HomoMedium::HomoMedium(const float &ta, const float &gg){
    tau = ta;
    g = gg;
}

/*
* Sample the interaction point and direction
*/
void HomoMedium::sample(const Ray &ray, float &t, Vector &wo, float &p, float &psurf, float &fr){
    t = - (log(1.0f - drand48())) / tau;
    p = tau * exp(- tau * t);
    float lambda = drand48(), cur = (1.0f - g * g) / (1.0f - g + 2.0f * g * lambda);
    float costheta = fabs(g) < eps ? (0.5f / g * (1.0f + g * g - cur * cur)) : 1.0f - 2.0f * lambda;
    float sintheta = sqrt(fmax(0.0f, 1.0f - costheta * costheta));
    float phi = drand48() * 2 * PI, sinphi = sin(phi), cosphi = cos(phi);
    Normal n(ray.direction);
    wo = n.toWorld(Vector(sintheta * sinphi, sintheta * cosphi, costheta));
    wo.normalize();
    fr = exp(- tau * t);
    psurf = exp(- tau * ray.tmax);
}

/*
* get the probability of arriving at a surface
*/
float HomoMedium::pSurf(const float &t){
    return exp(- tau * t);
}