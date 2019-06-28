#include <computation/geometry/color.h>

/*
* A method to convert float color to int RGBColor(0-255)
*/
Color Color::toRGB(){
    // protect uniform distribution
    Color RGBColor(x() * 256.0f - 1e-3, y() * 256.0f - 1e-3, z() * 256.0f - 1e-3);
    return RGBColor;
}