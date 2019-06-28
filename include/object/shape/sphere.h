#ifndef __OBJECT_SHAPE_SPHERE_H__
#define __OBJECT_SHAPE_SPHERE_H__

#include <object/shape/shape.h>

class Sphere : public Shape{
private:

    float radius;
    Point centre;
    Bbox bbox;

public:

    /*
    * Construction of a Sphere with centre point and radius
    */
    Sphere(const Point &cen, const float &rad);

    /*
    * The only useful method : intersection with a ray
    */
    virtual bool hasIntersection(const Ray &ray);
    virtual bool hasIntersection(const Ray &ray, Intersection& p);

    // find the boundings of the shape
    virtual Bbox getBbox();

    // get the surface area of the shape
    virtual float getArea();

    // sample points
    virtual float sample(Point &p, Normal &n);

    virtual void simplify(const float &threshold, const int &pointsLeft){}
};

#endif