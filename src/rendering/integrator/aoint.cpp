#include <rendering/integrator/aoint.h>
#include <computation/sample/mathdistri.h>

Color AoIntegrator::Lo(Scene* scene, const Ray &ray){
    Intersection p;
    bool inter = scene->hasIntersection(ray, p);
    if (!inter) return Color(0.0f, 0.0f, 0.0f);
    else{
        Sampler *sample = new UniformCosineSphereSampler();
        SampleData x = sample->sample();
        Vector outdirec = p.n.toWorld(Vector(x.p3));
        if (scene->hasIntersection(Ray(p.p, outdirec))) return Color(0.0f, 0.0f, 0.0f);
        else return Color(0.95f, 0.95f, 0.95f);
    }
}