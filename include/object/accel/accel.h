/*
This header file offers a method to accel ray - trianglemesh intersection.
*/

#ifndef __OBJECT_ACCEL_ACCEL_H__
#define __OBJECT_ACCEL_ACCEL_H__

#include <object/shape/shape.h>
#include <vector>

/*
* Base Class for All kinds of Shape Acceleration.
*/
class Accel{
public:
    virtual bool hasIntersection(const Ray &ray) = 0;
    virtual bool hasIntersection(const Ray &ray, Intersection& p) = 0;
    virtual void surfBuild(std::vector<int>* ptn, const float &threshold) = 0;
};

#endif