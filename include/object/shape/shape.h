#ifndef __OBJECT_SHAPE_SHAPE_H__
#define __OBJECT_SHAPE_SHAPE_H__

#include <computation/computation.h>
#include <object/material/materialhead.h>

class Shape{
private:
    bool isemit = false;
    Color emitter;
    BSDF *bsdf;
    BSSRDF *bssrdf;
public:

    /*
    * a method to find the Intersection of a ray with an object
    */
    virtual bool hasIntersection(const Ray &ray){}
    virtual bool hasIntersection(const Ray &ray, Intersection& p){}

    /*
    * find the boundings of the shape
    */
    virtual Bbox getBbox(){}

    /*
    * get the surface area of the shape
    */
    virtual float getArea(){}

    /*
    * sample points
    */
    virtual float sample(Point &p, Normal &n){}

    /*
    * add and get emitance
    */
    void addEmit(const Color &em);
    Color getEmit();
    bool isEmit();

    /*
    * add and get bsdf
    */
    void addBSDF(BSDF *b);
    BSDF* getBSDF();

    /*
    * add and get bssrdf
    */
    void addBSSRDF(BSSRDF *b);
    BSSRDF* getBSSRDF();

    virtual void simplify(const float &threshold, const float &pointsLeft) = 0;

};

#endif