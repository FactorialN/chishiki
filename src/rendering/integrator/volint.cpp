#include <rendering/integrator/volint.h>

Color VolIntegrator::Lo(Scene* scene, const Ray &ray){
    unsigned int bounce;
    Color beta(1.0f, 1.0f, 1.0f), ref(0.0f, 0.0f, 0.0f);
    Ray r = ray;
    Medium *medium = scene->getMedium();
    EnvironmentMap *envmap = scene->getEnvmap();

    for (bounce = 0; bounce < 10; ++bounce) {
        Normal n, nn;
        float psurf, pp, fr, spt = Inf, imp, kf, continu = 0.95, ps, dlp; 
        Color alb, cl;
        Vector wi, wo;
        Intersection p;
        Point po;
        bool foundIntersection = scene->hasIntersection(r, p);
        if (medium != nullptr) {
            medium->sample(Ray(r.origin, r.direction, p.t - eps), spt, wo, pp, psurf, fr);
        }

        if (beta.length() < eps)break;

        bool turned = false;
        if (medium != nullptr && spt < p.t){
            // sample in medium
            if (scene->hasLight()){
                scene->samplelight(r.calc(spt), po, nn, cl, ps);
                ref = ref + 0.3f * medium->pSurf((po - r.calc(spt)).length()) * beta.multi(cl);
            }
            beta = beta * fr * 0.7f;
            r = Ray(r.calc(spt), wo);
            turned = true;
        }
        else{
            // compute direct light in this bounce
            if (foundIntersection){
                if (scene->getShape(p.obj)->isEmit()){
                    ref = ref + beta.multi(scene->getShape(p.obj)->getEmit()) / (p.t * p.t);
                    break;
                }
            }
            else{
                if (envmap != nullptr)
                    ref = ref + beta.multi(envmap->getColor(r.direction));
                break;
            }

            wi = r.direction;
            n = p.n;
            Shape *shape = scene->getShape(p.obj);
            BSDF *bsdf = shape->getBSDF();
            BSSRDF *bssrdf = shape->getBSSRDF();

            // sampling bsdf for common objects
            if (bsdf != nullptr){
                dlp = bsdf->isContinue() ? 0.3f : 0.0f;
                if (scene->hasLight()){
                    scene->samplelight(p.p, po, nn, cl, ps);
                    Vector dn = po - p.p;
                    dn.normalize();
                    float fr = bsdf->fr(n.toLocal(wi), n.toLocal(dn));
                    ref = ref + dlp * beta.multi(bsdf->color(fr * fabs(n * dn) * cl));
                }
                bsdf->sample(n.toLocal(wi), wo, imp, kf, alb);
                beta = beta.multi(alb) * (kf / imp) * (1.0f - dlp);
                r = Ray(p.p, n.toWorld(wo));
                turned = true;
            }

            /*
            * BSSRDF sampling
            * Lo(po, wo) = \int_{A} \int_{w} f_r(po, wo, pi, wi) * Lo(pi, wi)
            * Lo(po, wo) = \Sigma(f_r(po, wo, pis, wis) * Lo(pis, wis) / ps)/N
            * Sample from 2 kinds of light: path tracing(70%) and light source(30%)
            */
            if (bssrdf != nullptr){
                Point sp1, sp2;
                float rs, fr, pps;
                Intersection pp;
               
                if (scene->hasLight()){
                    Point po;
                    Normal nn;
                    float ps;
                    Color cl;
                    scene->samplelight(p.p, po, nn, cl, ps);
                    Vector dn = po - p.p;
                    float dis = dn.length();
                    dn.normalize();
                    fr = 1.0f / ((dis + 1.0f) * (dis + 1.0f));
                    ref = ref + 0.3f * beta.multi(fr * fabs(n * dn) * cl);
                }
                
                bssrdf->sample_r(rs, ps, fr);
                Sampler *sample = new UniformHemiSphereSampler();
                sp1 = p.p + rs * n.toWorld(sample->sample().p3);
                sp2 = p.p - rs * n.toWorld(sample->sample().p3);
                bool tag = shape->hasIntersection(Ray(sp1, sp2 - sp1, (sp2 - sp1).length()), pp);
                if (tag){
                    po = pp.p;
                    nn = pp.n;
                    bssrdf->sample_w(p.p, n.toLocal(wi), wo, pps);
                    beta = fr * beta / (ps * pps) * 0.7f;
                    r = Ray(po, nn.toWorld(wo));
                    turned = true;
                }
            }
        }

        if(turned && drand48() < continu){
                beta = beta / continu;
        }
        else break;
    }

    return ref;
}