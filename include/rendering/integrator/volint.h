/*
A Volume Path Tracer.
*/

#ifndef __RENDERING_INTEGRATOR_VOLINT_H__
#define __RENDERING_INTEGRATOR_VOLINT_H__

#include <rendering/integrator/integratorbase.h>

class VolIntegrator : public Integrator{
public:
    virtual Color Lo(Scene* scene, const Ray &ray);
};

#endif