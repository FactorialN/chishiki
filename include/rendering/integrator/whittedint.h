/*
A Whitted-Style Path Tracer.
*/

#ifndef __RENDERING_INTEGRATOR_WHITTEDINT_H__
#define __RENDERING_INTEGRATOR_WHITTEDINT_H__

#include <rendering/integrator/integratorbase.h>

class WhittedIntegrator : public Integrator{
public:
    Color Lo(Scene* scene, const Ray &ray, const bool &lst, const int &depth);
    virtual Color Lo(Scene* scene, const Ray &ray);
};

#endif