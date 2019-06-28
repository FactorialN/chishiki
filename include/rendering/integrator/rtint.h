/*
This integrator renders the object with normal ray tracing method.
*/

#ifndef __RENDERING_INTEGRATOR_RTINT_H__
#define __RENDERING_INTEGRATOR_RTINT_H__

#include <rendering/integrator/integratorbase.h>

class RtIntegrator : public Integrator{
public:
    virtual Color Lo(Scene* scene, const Ray &ray);
};

#endif