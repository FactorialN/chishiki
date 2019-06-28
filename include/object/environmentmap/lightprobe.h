/*
This class defines an environment map in the background.
*/

#ifndef __OBJECT_ENVIRONMENTMAP_LIGHTPROBE_H__
#define __OBJECT_ENVIRONMENTMAP_LIGHTPROBE_H__

#include <computation/computation.h>
#include <object/environmentmap/envmapbase.h>

/*
* EnvironmentMap light source
*/
class Lightprobe : public EnvironmentMap{
private:
    Color **cl;
    int widx, widy;
public:

    /*
    * Construction from a P3 .ppm file
    */
    Lightprobe(char *ch);

    /*
    * desctruct the envmap
    */
    ~Lightprobe();

    /*
    * normalize a calculated projection to (-0.5, 0.5)
    */
    float normalize(const float &x);

    /*
    * get the color of environment background in a given direction
    */
    Color getColor(const Vector& d);
};

#endif