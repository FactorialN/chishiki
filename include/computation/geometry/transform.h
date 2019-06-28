/*
This header file defines the basic types of Transformations, please add more methods of transform here.
*/

#ifndef __COMPUTATION_GEOMETRY_TRANSFORM_H__
#define __COMPUTATION_GEOMETRY_TRANSFORM_H__

#include <computation/linear/linearhead.h>
#include <computation/geometry/ray.h>
#include <computation/geometry/bbox.h>


/*
* Transform is actually a Matrix.
*/
class Transform : public HomoMatrix{
public:
    Transform() : HomoMatrix(){}
    Transform(const float x[4][4]) : HomoMatrix(x){}
};

/*
* Basic Types of Linear Transforms.
*/
class TranslateTransform : public Transform{
public:
    TranslateTransform(const float &dx, const float &dy, const float &dz);
};

class ScaleTransform : public Transform{
public:
    ScaleTransform(const float &sx, const float &sy, const float &sz);
};

class RotationTransform : public Transform{
public:
    RotationTransform(const Vector& a, const float &theta);
};

#endif