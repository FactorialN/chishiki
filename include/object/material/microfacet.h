/*
Microfacet Reflection Model.
*/

#ifndef __OBJECT_MATERIAL_MICROFACET_H__
#define __OBJECT_MATERIAL_MICROFACET_H__

#include <object/material/bsdf.h>

class Microfacet : public BSDF{
private:
    Color kd;
    float alpha, ks;
public:
    Microfacet(const Color &Kd, const float &al);

    virtual float fr(const Vector &wi, const Vector &wo);
    virtual void sample(const Vector &wi, Vector &wo, float &p, float &kf, Color &alb);
    virtual Color color(const Color &Li);

    float Dc(const Vector &wh);
    float Gc(const Vector &wv,const Vector &wh);

    virtual bool isContinue();
};

#endif