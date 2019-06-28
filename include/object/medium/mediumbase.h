/*
* This header defines the Base Class of all volume mediums.
*/

#ifndef __OBJECT_MEDIUM_MEDIUMBASE_H__
#define __OBJECT_MEDIUM_MEDIUMBASE_H__

#include <computation/computation.h>

class Medium{
public:
    /*
    * Sample a point and a direction in the medium
    */
    virtual void sample(const Ray &ray, float &t, Vector &wo, float &p, float &psurf, float &fr) = 0;

    /*
    * get the probability of arriving at a surface
    */
    virtual float pSurf(const float &t) = 0;
};

#endif