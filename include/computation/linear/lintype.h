/*
* This file realized the class Point, Vector, Normal and the basic calculation between them.
*/

#ifndef __COMPUTATION_LINEAR_LINTYPE_H__
#define __COMPUTATION_LINEAR_LINTYPE_H__

#include <computation/linear/homo.h>

/*
* A class of 2-d Points
*/
template <class T>
struct Point2{
    T a, b;
};

/*
* A class of 3-d points.
*/
class Point : public HomoVector{
public:
    Point():HomoVector(0.0, 0.0, 0.0, 1.0){}
    Point(const float &x, const float &y, const float &z):HomoVector(x, y, z, 1.0){}
    Point(const HomoVector& b):HomoVector(b.x(), b.y(), b.z(), 1.0){}
};

/*
* A class of 3-d vectors.
*/
class Vector : public HomoVector{
public:
    Vector():HomoVector(0.0, 0.0, 0.0, 0.0){}
    Vector(const float &x, const float &y, const float &z):HomoVector(x, y, z, 0.0){}
    Vector(const HomoVector& b):HomoVector(b.x(), b.y(), b.z(), 0.0){}
};

/*
* A class of 3-d normals.
*/
class Normal : public HomoVector{
public:
    Normal():HomoVector(0.0, 0.0, 0.0, 0.0){}
    Normal(const float &x, const float &y, const float &z):HomoVector(x, y, z, 0.0){normalize();}
    Normal(const HomoVector& b):HomoVector(b.x(), b.y(), b.z(), 0.0){normalize();}
    void plateBase(Vector &v1, Vector &v2); // find 2 base of the surface
    Vector toWorld(const Vector &p);
    Vector toLocal(const Vector &p);
};

#endif