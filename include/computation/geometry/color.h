/*
* This file defines the base class of color.
*/

#ifndef __COMPUTATION_GEOMETRY_COLOR_H__
#define __COMPUTATION_GEOMETRY_COLOR_H__

#include <computation/linear/linearhead.h>


/*
* Color class is from Vector class
*/
class Color : public Vector{
public:
    /*
    * Several Ways to Construct a Color Object
    */
    Color():Vector(0.0f, 0.0f, 0.0f){}
    Color(const float &x, const float &y, const float &z) : Vector(x, y, z){}
    Color(const HomoVector& b) : Vector(b.x(), b.y(), b.z()){}
    
    /*
    * A method to convert float color to int RGBColor(0-255)
    */
    Color toRGB();
};
#endif