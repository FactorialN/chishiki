/*
This integrator renders the object with the color of normal.
*/

#ifndef __RENDERING_INTEGRATOR_NORMALDIFF_H__
#define __RENDERING_INTEGRATOR_NORMALDIFF_H__

#include <rendering/integrator/integratorbase.h>

class NormalDiffIntegrator : public Integrator{
public:
    virtual Color Lo(Scene* scene, const Ray &ray);
};

#endif