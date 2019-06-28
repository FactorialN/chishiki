/*
This header file defines the basic interface of a bounding box.
*/

#ifndef __COMPUTATION_GEOMETRY_BBOX_H__
#define __COMPUTATION_GEOMETRY_BBOX_H__

#include <computation/geometry/ray.h>

class Bbox{
public:
    /*
    * Several ways to construct a bounding box
    */
    Bbox(){
        vi[0] = vi[1] = vi[2] = Inf;
        vm[0] = vm[1] = vm[2] = -Inf;
    }
    Bbox(const Point &a){
        vi[0] = vm[0] = a.val(0);
        vi[1] = vm[1] = a.val(1);
        vi[2] = vm[2] = a.val(2);
    }
    Bbox(const Point &mi, const Point &mx){
        vi[0] = mi.val(0); 
        vm[0] = mx.val(0);
        vi[1] = mi.val(1); 
        vm[1] = mx.val(1);
        vi[2] = mi.val(2); 
        vm[2] = mx.val(2);
    }

    /*
    * Modification to the current bounding box
    */
    void extend(const Point &a);

    /*
    * Operation between bounding boxes
    */
    void extend(const Bbox &b){
        extend(b.maxPoint());
        extend(b.minPoint());
    }
    bool hasIntersect(const Bbox &b);
    Bbox intersect(const Bbox &b);

    /*
    * find the son-bbox of the bbox
    */
    Bbox getSBbox(const int &j);

    /*
    * Several basic calculation about the bounding box
    */
    Point maxPoint()const{return Point(vm[0], vm[1], vm[2]);}
    Point minPoint()const{return Point(vi[0], vi[1], vi[2]);}
    Point midPoint()const{return Point((vm[0] + vi[0]) * 0.5f, (vm[1] + vi[1]) * 0.5f, (vm[2] + vi[2]) * 0.5f);}
    
    /*
    * Ray-Bounding Intersection.
    */
    bool hasIntersect(const Ray &r, float &t);

    /*
    * Standard output a bbox
    */
    void output();
private:
    float vi[4], vm[4];
};

#endif