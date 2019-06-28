/*
* Base class of BSSRDFs.
*/

#ifndef __OBJECT_MATERIAL_BSSRDF_H__
#define __OBJECT_MATERIAL_BSSRDF_H__

#include <computation/computation.h>

class BSSRDF{
public:
    virtual void sample_r(float &r, float &p, float &fr) = 0;
    virtual void sample_w(const Point &po , const Vector &wo, Vector &wi, float &p) = 0;
    virtual void sample_s() = 0;
    virtual void sample_sp(const Normal &n) = 0;
};

#endif