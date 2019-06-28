#include <rendering/integrator/rtint.h>

Color RtIntegrator::Lo(Scene* scene, const Ray &ray){
    Intersection p;
    if (!scene->hasIntersection(ray, p)){
        EnvironmentMap* envmap = scene->getEnvmap();
        if(envmap == nullptr)return Color(0.0f, 0.0f, 0.0f);
        else return envmap->getColor(ray.direction);
    }
    Shape *obj = scene->getShape(p.obj);
    if (obj->isEmit()){
        return obj->getEmit() / (p.t * p.t);
    }

    BSDF *bsdf = obj->getBSDF();
    Vector wi = ray.direction, wo;
    Normal n = p.n;
    float imp, kf;
    Color alb;
    bsdf->sample(n.toLocal(wi), wo, imp, kf, alb);
    float continu = 0.95;
    if(drand48() < continu) return alb.multi(Lo(scene, Ray(p.p, n.toWorld(wo)))) * kf / continu / imp;
    else return Color(0.0f, 0.0f, 0.0f);
}