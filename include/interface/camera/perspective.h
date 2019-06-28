/*
Perspective camera.
*/

#ifndef __OBJECT_CAMERA_PERSPECTIVE_H__
#define __OBJECT_CAMERA_PERSPECTIVE_H__

#include <interface/camera/camerabase.h>
#include <interface/camera/film.h>
#include <computation/computation.h>
#include <computation/sample/mathdistri.h>

class PerspectiveCamera : public Camera{
private:
    Point viewPoint, lookatPoint;
    Normal inVec, direcVec, xVec;
    Film *film;
    int widx, widy, nSamples;
    float k, revsp, f;
    Sampler *sampler;
public:
    
    // Construct Perspective camera with 
    PerspectiveCamera(const Point &v, const Point &l, const Vector &u, const int &x, const int &y, const int &sps, const float &ff);

    void conduct(const int &x, const int &y, Scene *scene);
    
    // render the scene
    virtual void shot(Scene *scene);

    // output the rendered graph
    virtual void output(FILE *p);
};

#endif