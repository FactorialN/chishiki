#include <rendering/integrator/whittedint.h>

Color WhittedIntegrator::Lo(Scene* scene, const Ray &ray, const bool &lst, const int &depth){
    Intersection p;
    if (depth > 15) return Color(0.0f, 0.0f, 0.0f);
    if (!scene->hasIntersection(ray, p)){
        EnvironmentMap* envmap = scene->getEnvmap();
        if(envmap == nullptr)return Color(0.0f, 0.0f, 0.0f);
        else return envmap->getColor(ray.direction);
    }
    Shape *obj = scene->getShape(p.obj);
    if (obj->isEmit()){
        if(!lst) return obj->getEmit() / (p.t * p.t);
        else return Color(0.0f, 0.0f, 0.0f);
    }

    Color ref = Color(0.0f, 0.0f, 0.0f);
    BSDF *bsdf = obj->getBSDF();
    Vector wi = ray.direction, wo;
    Normal n = p.n;
    
    // calculate direct illumination on continuous bsdf
    if (bsdf->isContinue()){
        uint32_t semit = 0, ns = scene->getObjs();
        uint32_t *eobj = new uint32_t[ns + 2];
        float *sobj = new float[ns + 2];
        for (uint32_t i = 0; i < ns; i++)
            if(scene->getShape(i)->isEmit()){
                eobj[semit] = i;
                sobj[semit++] = scene->getShape(i)->getArea();
            }
        if (semit > 0){
            Sampler *wts = new WeightedSampler(semit, sobj);
            SampleData xx = wts->sample();
            Point po;
            Normal nn;
            float ps = xx.Float * scene->getShape(eobj[xx.uInt])->sample(po, nn);
            Vector d = po - p.p, dn = d;
            float dis = d.length();
            float fr = bsdf->fr(n.toLocal(wi), n.toLocal(dn));
            dn.normalize();
            if (!scene->hasIntersection(Ray(p.p, dn, eps, dis - eps))){
                ref = fr * scene->getShape(eobj[xx.uInt])->getEmit() * fmax(0.0f, - 1.0f * nn * dn) * fabs(n * dn) / (dis * dis * ps);
                ref = bsdf->color(ref);
            }
        }
        delete[] eobj;
        delete[] sobj;
    }
    
    // indirect illumination for continuous or all for discrete(specular)
    float imp, kf;
    Color alb;
    bsdf->sample(n.toLocal(wi), wo, imp, kf, alb);
    if (bsdf->isContinue()){
        float continu = 0.95;
        if(drand48() < continu) ref = ref + alb.multi(Lo(scene, Ray(p.p, n.toWorld(wo)), true, depth + 1)) * kf / continu / imp;
    }
    else ref = ref + bsdf->color(Lo(scene, Ray(p.p, n.toWorld(wo)), false, depth + 1)) * kf / imp;
    return ref;
}

Color WhittedIntegrator::Lo(Scene* scene, const Ray &ray){
    return Lo(scene, ray, false, 1);
}