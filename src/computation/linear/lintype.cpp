#include <computation/linear/lintype.h>


/*
* find 2 roots of the normal vector coordinate system
*/
void Normal::plateBase(Vector &v1, Vector &v2){
    v1 = x() < 0 ? (*this % Vector(1.0f, 0.0f, 0.0f)) : (*this % Vector(-1.0f, 0.0f, 0.0f));
    v2 = *this % v1;
    v1.normalize();
    v2.normalize();
}

Vector Normal::toWorld(const Vector &p){
    Vector v1, v2;
    plateBase(v1, v2);
    return Vector(v1 * p.x() + v2 * p.y() + (*this) * p.z());
}

Vector Normal::toLocal(const Vector &p){
    Vector v1, v2;
    plateBase(v1, v2);
    return Vector(v1 * p, v2 * p, (*this) * p);
}