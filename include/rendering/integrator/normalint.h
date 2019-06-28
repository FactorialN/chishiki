/*
This integrator renders the object with the color of normal.
*/

#ifndef __RENDERING_INTEGRATOR_NORMALINT_H__
#define __RENDERING_INTEGRATOR_NORMALINT_H__

#include <rendering/integrator/integratorbase.h>

class NormalIntegrator : public Integrator{
public:
    virtual Color Lo(Scene* scene, const Ray &ray);
};

#endif