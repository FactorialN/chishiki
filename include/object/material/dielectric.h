/*
Basic Dielectric Material.
*/

#ifndef __OBJECT_MATERIAL_DIELECTRIC_H__
#define __OBJECT_MATERIAL_DIELECTRIC_H__

#include <object/material/bsdf.h>

class Dielectric : public BSDF{
private:
    Color albedo;
    float eta;
public:
    Dielectric(const Color &alb, const float &e);

    virtual float fr(const Vector &wi, const Vector &wo);
    virtual void sample(const Vector &wi, Vector &wo, float &p, float &kf, Color &alb);
    virtual Color color(const Color &Li);

    virtual bool isContinue();
};

#endif