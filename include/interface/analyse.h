/*
This file analyses the scenario, builds the basic rendering object, and conducts rendering.
*/

#ifndef __INTERFACE_ANALYSE_H__
#define __INTERFACE_ANALYSE_H__

#include <object/scene.h>
#include <interface/camera/camerahead.h>

class Analyse{
private:
    char *filename;
    Scene *scene;
    Camera *camera;
    bool isSimplify = false;
public:
    Analyse(char *fn);
    
    // conduct rendering
    void run();

};

#endif