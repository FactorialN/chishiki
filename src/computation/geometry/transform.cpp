#include <computation/geometry/transform.h>

TranslateTransform:: TranslateTransform(const float &dx, const float &dy, const float &dz){
    float d[4][4]={
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 
        0.0f, 0.0f, 1.0f, 0.0f,
        dx  , dy  , dz  , 1.0f
    };
    Modify(d);
}

ScaleTransform:: ScaleTransform(const float &sx, const float &sy, const float &sz){
    float d[4][4]={
        sx  , 0.0f, 0.0f, 0.0f,
        0.0f, sy  , 0.0f, 0.0f, 
        0.0f, 0.0f, sz  , 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    Modify(d);
}

RotationTransform:: RotationTransform(const Vector& a, const float &theta){
    Normal v1 = a.x() < 0?(a % Vector(1.0f, 0.0f, 0.0f)):(a % Vector(-1.0f, 0.0f, 0.0f));
    Normal v2 = a % v1;
    // a, v1, v2 are othonormal
    // TO DO
}