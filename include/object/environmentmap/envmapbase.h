/*
This class defines an environment map in the background.
*/

#ifndef __OBJECT_ENVIRONMENTMAP_ENVMAPBASE_H__
#define __OBJECT_ENVIRONMENTMAP_ENVMAPBASE_H__

#include <computation/computation.h>


/*
* EnvironmentMap light source
*/
class EnvironmentMap{
public:
    /*
    * get the color of environment background in a given direction
    */
    virtual Color getColor(const Vector& d) = 0;
};

#endif