/*
* Seperable BSSRDF.
*/

#ifndef __OBJECT_MATERIAL_SEPERABLE_H__
#define __OBJECT_MATERIAL_SEPERABLE_H__

#include <object/material/bssrdf.h>

class SeperableBSSRDF : public BSSRDF{
private:
    float EPS, rr;
public:
    SeperableBSSRDF(const float &e, const float &r);
    void sample_r(float &r, float &p, float &fr);
    void sample_w(const Point &po , const Vector &wo, Vector &wi, float &p);
    virtual void sample_s();
    virtual void sample_sp(const Normal &n);
};

#endif