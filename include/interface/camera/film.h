/*
This header declared a class 'Film' for cameras.
*/

#ifndef __OBJECT_CAMERA_FILM_H__
#define __OBJECT_CAMERA_FILM_H__

#include <computation/computation.h>

class Film{
private:
    Color **cl;
    int widx, widy;
public:

    // Construct a film with x and y
    Film(const int &x, const int &y);

    // Insert a sampled color
    void addColor(const int &x, const int &y, const Color &c);

    // output
    void output(FILE *f);
};

#endif