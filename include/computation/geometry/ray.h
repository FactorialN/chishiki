/*
This header file defines the basic interface of a ray.
*/

#ifndef __COMPUTATION_GEOMETRY_RAY_H__
#define __COMPUTATION_GEOMETRY_RAY_H__

#include <computation/linear/linearhead.h>

class Ray{
public:
    /*
    * Construction of the Ray
    */
    Ray(const Point &a, const Vector &b, float tm = Inf){
        origin = a; direction = b; direction.normalize();
        tmin = eps; tmax = tm;
    }
    Ray(const Point &a, const Vector &b, float ti, float tm){
        origin = a; direction = b; direction.normalize();
        tmin = ti; tmax = tm;
    }
    Ray(){}

    /*
    * Calculation of the Ray
    */
    Point calc(const float &t)const{return Point(origin.x() + t * direction.x(), origin.y() + t * direction.y(), origin.z() + t * direction.z());}
    Point Origin()const{return origin;}
    Vector Direction()const{return direction;}
    Point origin;
    Vector direction;
    float tmin, tmax;
};
#endif