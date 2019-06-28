#include <computation/geometry/triangle.h>
#include <cstdio>
#include <algorithm>


/*
* Construct Triangle without per-point normals
*/
Triangle::Triangle(const Point &x, const Point &y, const Point &z){
    A = x;
    B = y;
    C = z;
    n = Normal((y - x) % (y - z));
    norType = 1;
}

/*
* Construct Triangle with point identifiers, without per-point normals
*/
Triangle::Triangle(const Point &x, const Point &y, const Point &z, const int &px, const int &py, const int &pz){
    A = x;
    B = y;
    C = z;
    n = Normal((y - x) % (y - z));
    pA = px;
    pB = py;
    pC = pz;
    norType = 1;
}

/*
* Ray-triangle intersection.
*/
bool Triangle::hasIntersection(const Ray &ray, Intersection &p){
    p.t = Inf;

    // calculate ray-surface intersection
    Normal nhlp = (B - A) % (C - A);
    float D = - (nhlp * A);
    float t = (- D - (nhlp * ray.origin)) / (nhlp * ray.direction);
    if (fabs(nhlp * ray.direction) < eps) return false;
    if (t > ray.tmax || t < ray.tmin) return false;
    p.p = ray.calc(t);

    // solve v2 = u * v0 + v * v1
    Vector v0 = B - A, v1 = C - A, v2 = p.p - A;
    float v00 = v0 * v0, v01 = v0 * v1, v11 = v1 * v1, v12 = v1 *v2, v02 = v0 * v2;
    float inv = 1.0f / (v00 * v11 - v01 * v01);
    float u = inv * (v11 * v02 - v01 * v12);
    float v = inv * (v00 * v12 - v01 * v02);

    // in the triangle <=> u, v >= 0, u + v <= 1
    if (u < 0.0f || v < 0.0f || u + v > 1.0f) return false;
    p.uv.a = u;
    p.uv.b = v;

    // calculate the normal vector at p.p
    if (norType == 1) p.n = nhlp;
    else p.n = Normal(nA * (1 - u - v) + nB * u + nC * v);
    p.t = t;
    return true;
}


/*
* Calculate the bounding box of this triangle
*/
Bbox Triangle::getBbox(){
    Bbox a = Bbox(A);
    a.extend(B);
    a.extend(C);
    return a;
}


/*
* Calculate the Area of this triangle with %
*/
float Triangle::getArea(){
    return ((B - A) % (C - A)).length() * 0.5;
}


/*
* Sample a point on the triangle
*/
Point Triangle::sample(Normal &n){
    float u = drand48(), v = drand48();
    // this make it uniform at 1 sample
    if (u + v > 1.0f){
        u = 1.0f - u;
        v = 1.0f - v;
    }
    if (norType == 1) n = (B - A) % (C - A);
    else n = Normal(nA * (1 - u - v) + nB * u + nC * v);
    return (B - A) * u + (C - A) * v + A;
}


/*
* generator 3 edge vector
*/
void Triangle::getPoints(Point &p1, Point &p2, Point &p3, int &x1, int &x2, int &x3){
    p1 = A; p2 = B; p3 = C;
    x1 = pA; x2 = pB; x3 = pC;
}

HomoVector Triangle::surfaceEqua(){
    Normal nhlp = (B - A) % (C - A);
    float D = - (nhlp * A);
    return HomoVector(nhlp.x(), nhlp.y(), nhlp.z(), D);
}