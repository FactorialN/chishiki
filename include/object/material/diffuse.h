/*
Basic Diffuse Material.
*/

#ifndef __OBJECT_MATERIAL_DIFFUSE_H__
#define __OBJECT_MATERIAL_DIFFUSE_H__

#include <object/material/bsdf.h>

class Diffuse : public BSDF{
private:
    Color albedo;
public:
    // Construction of Diffuse BRDF Model: only color needed
    Diffuse(const Color &alb);

    virtual float fr(const Vector &wi, const Vector &wo);
    virtual void sample(const Vector &wi, Vector &wo, float &p, float &kf, Color &alb);
    virtual Color color(const Color &Li);

    virtual bool isContinue();
};

#endif