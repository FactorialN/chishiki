/*
This integrator renders the object with ao.
*/

#ifndef __RENDERING_INTEGRATOR_AOINT_H__
#define __RENDERING_INTEGRATOR_AOINT_H__

#include <rendering/integrator/integratorbase.h>

class AoIntegrator : public Integrator{
public:
    virtual Color Lo(Scene* scene, const Ray &ray);
};

#endif