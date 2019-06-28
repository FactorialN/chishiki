#ifndef __COMPUTATION_GEOMETRY_INTERSECTION_H__
#define __COMPUTATION_GEOMETRY_INTERSECTION_H__

#include <computation/linear/linearhead.h>
#include <computation/geometry/ray.h>

/*
* This struct saves the params of a ray-object intersection.
*/
struct Intersection{
    Normal n; // the normal at the intersection point
    Point p; // the intersection point
    Point2f uv; // (u, v) norm of the intersection point
    float t; // the intersection t
    int obj; // object number
    Intersection(){}
};

#endif