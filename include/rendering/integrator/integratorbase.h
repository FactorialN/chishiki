/*
The base class of all integrators
*/

#ifndef __RENDERING_INTEGRATOR_INTEGRATORBASE_H__
#define __RENDERING_INTEGRATOR_INTEGRATORBASE_H__

#include <computation/computation.h>
#include <object/scene.h>

class Integrator{
public:
    virtual Color Lo(Scene* scene, const Ray &ray) = 0;
};

#endif