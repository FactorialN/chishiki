/*
Base class of all cameras.
*/

#ifndef __OBJECT_CAMERA_CAMERABASE_H__
#define __OBJECT_CAMERA_CAMERABASE_H__

#include <cstdio>
#include <rendering/integrator/integratorhead.h>
#include <object/scene.h>

class Camera{
public:
    virtual void shot(Scene *scene){}
    virtual void output(FILE *p){}
    void addInt(Integrator *re) { render = re;}
    Integrator *render;
};

#endif