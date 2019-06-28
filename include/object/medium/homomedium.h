#ifndef __OBJECT_MEDIUM_HOMOMEDIUM_H__
#define __OBJECT_MEDIUM_HOMOMEDIUM_H__

#include <object/medium/mediumbase.h>

/*
* Homogeneous Medium
*/
class HomoMedium : public Medium{
private:
    float tau, g;
public:
    HomoMedium(const float &ta, const float &gg);

    /*
    * Sample a point and a direction in the homomedium
    */
    virtual void sample(const Ray &ray, float &t, Vector &wo, float &p, float &psurf, float &fr);

    /*
    * get the probability of arriving at a surface
    */
    virtual float pSurf(const float &t);
};

#endif