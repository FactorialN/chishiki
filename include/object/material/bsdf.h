/*
* Base class of all reflection models.
*/

#ifndef __OBJECT_MATERIAL_REFLECTION_H__
#define __OBJECT_MATERIAL_REFLECTION_H__

#include <computation/computation.h>

/*
* bidirectional scattering distribution funtion
*/
class BSDF{
public:
    virtual float fr(const Vector &wi, const Vector &wo) = 0;
    virtual void sample(const Vector &wi, Vector &wo, float &p, float &kf, Color &alb) = 0;
    virtual Color color(const Color &Li) = 0;

    /*
    *  a method to determine the property of this material for integrators
    */
    virtual bool isContinue() = 0;
};

#endif