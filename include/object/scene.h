/*
Saves everything in the scene.
*/

#ifndef __OBJECT_SCENE_H__
#define __OBJECT_SCENE_H__

#include <object/shape/shapehead.h>
#include <object/environmentmap/envmaphead.h>
#include <object/medium/mediumhead.h>
#include <vector>

class Scene{
private:

    std::vector<Shape*> obj;
    int objs;
    EnvironmentMap *envmap;
    Medium *medium;
    bool prepd;
    WeightedSampler *wts;
    unsigned int *eobj;

public:

    // Scene class should be constructed with default construtor, and set 
    Scene();

    // these methods are for adding things in the scene
    void addShape(Shape *s);
    void addEnvmap(EnvironmentMap *env);
    void addMedium(Medium *m);

    // intersection
    bool hasIntersection(const Ray &ray);
    bool hasIntersection(const Ray &ray, Intersection& p);

    // get an object
    Shape* getShape(const int &k);
    EnvironmentMap* getEnvmap();
    Medium* getMedium();
    int getObjs();

    // preparation before the rendering procedure
    void prep();

    // Sample a light source point in the scene
    void samplelight(const Point &pi, Point &po, Normal &nn, Color &param, float &p);

    // Find out whether emit shapes exists
    bool hasLight();
};

#endif