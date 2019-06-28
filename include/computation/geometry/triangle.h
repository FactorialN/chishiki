/*
This header file defines the basic interface of a triangle.
*/

#ifndef __COMPUTATION_GEOMETRY_TRIANGLE_H__
#define __COMPUTATION_GEOMETRY_TRIANGLE_H__

#include <computation/linear/linearhead.h>
#include <computation/geometry/intersection.h>
#include <computation/geometry/bbox.h>


/*
* Triangle: A basic geometry class.
*/
class Triangle{
private:
    Point A, B, C;
    Normal n, nA, nB, nC;
    int norType, pA, pB, pC;
public:
    /*
    * Construct a Triangle with / without normal given
    */
    Triangle(){}
    Triangle(const Point &x, const Point &y, const Point &z);
    Triangle(const Point &x, const Point &y, const Point &z, const int &px, const int &py, const int &pz);
    Triangle(const Point &x, const Point &y, const Point &z, const Normal &N):A(x), B(y), C(z), n(N), norType(1){}
    Triangle(const Point &x, const Point &y, const Point &z, const Normal &nx, const Normal &ny, const Normal &nz):A(x), B(y), C(z), nA(nx), nB(ny), nC(nz), norType(2){}
    Triangle(const Point &x, const Point &y, const Point &z, const Normal &nx, const Normal &ny, const Normal &nz, const int &px, const int &py, const int &pz):A(x), B(y), C(z), nA(nx), nB(ny), nC(nz), pA(px), pB(py), pC(pz), norType(2){}

    /*
    * Triangle Intersection with a ray
    */
    bool hasIntersection(const Ray &ray, Intersection &p);

    /*
    * Bounding of the triangle
    */
    Bbox getBbox();

    // calculate the area of the triangle
    float getArea();

    // sample a point in the triangle
    Point sample(Normal &n);

    // generate 3 Points
    void getPoints(Point &p1, Point &p2, Point &p3, int &x1, int &x2, int &x3);

    // generate the homovector of the surface
    HomoVector surfaceEqua();
};

#endif