/*
This header file defines the basic interface of a trianglemesh, constructed from a .obj file
*/

#ifndef __OBJECT_SHAPE_TRIANGLEMESH_H__
#define __OBJECT_SHAPE_TRIANGLEMESH_H__

#include <object/shape/shape.h>
#include <object/accel/accelhead.h>
#include <computation/computation.h>

struct SimplifyCompare{
    int A, B;
    Point C;
    HomoMatrix Q;
    float val;
    SimplifyCompare(const int &x, const int &y, const Point &z, const float &v):A(x), B(y), C(z), val(v){}
    SimplifyCompare(const int &x, const int &y, const Point &z, const float &v, const HomoMatrix &q):A(x), B(y), C(z), val(v), Q(q){}
    bool operator<(const SimplifyCompare &b)const{return val > b.val;}
};

class TriangleMesh : public Shape{
private:
    Triangle *meshes;
    Point *ppoints;
    unsigned int nmesh, npoints;
    Accel *a;
    Bbox bbox;
    float area;
    WeightedSampler *wts;

    // helps decoding the face vector in .obj file
    void decode(const std::string& s, unsigned int &a, unsigned int &b);

public:

    TriangleMesh(char *fn);

    /*
    * The only useful method : intersection with a ray
    */
    bool hasIntersection(const Ray &ray);
    bool hasIntersection(const Ray &ray, Intersection& p);

    // find the boundings of the shape
    virtual Bbox getBbox();

    // get the surface area of the shape
    virtual float getArea();

    // sample points
    virtual float sample(Point &p, Normal &n);

    // simplify using quadric error metrices
    void constructMIDV(const Point &V1, const Point &V2, const HomoMatrix &Q, Point &v, float &err);
    virtual void simplify(const float &threshold, const float &pointsLeft);
};

#endif