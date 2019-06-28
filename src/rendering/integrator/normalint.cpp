#include <rendering/integrator/normalint.h>

Color NormalIntegrator::Lo(Scene* scene, const Ray &ray){
    Intersection p;
    bool inter = scene->hasIntersection(ray, p);
    if (!inter) return Color(0.0f, 0.0f, 0.0f);
    else return Color(p.n.vecAbs());
}