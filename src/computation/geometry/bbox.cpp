#include <computation/geometry/bbox.h>
#include <cstdio>

/*
* Extend the bounding box with a point
*/
void Bbox::extend(const Point &a){
    for (unsigned int k = 0; k < 3; k++){
        vi[k] = fmin(vi[k], a.val(k));
        vm[k] = fmax(vm[k], a.val(k));
    }
}

/*
* Whether there's intersection between 2 bbox
*/
bool Bbox::hasIntersect(const Bbox &b){ 
    float wi[4], wx[4];
    Point ai = minPoint(), ax = maxPoint(), bi = b.minPoint(), bx = b.maxPoint();
    for (unsigned int k = 0; k < 3; k++){
        wi[k] = fmax(ai.val(k), bi.val(k));
        wx[k] = fmin(ax.val(k), bx.val(k));
    }
    return wi[0] <= wx[0] && wi[1] <= wx[1] && wi[2] <= wx[2];
}

/*
* get the intersection of 2 bbox
*/
Bbox Bbox::intersect(const Bbox &b){
    float wi[4], wx[4];
    Point ai = minPoint(), ax = maxPoint(), bi = b.minPoint(), bx = b.maxPoint();
    for (unsigned int k = 0; k < 3; k++){
        wi[k] = fmax(ai.val(k), bi.val(k));
        wx[k] = fmin(ax.val(k), bx.val(k));
    }
    Bbox c(Point(wi[0], wi[1], wi[2]), Point(wx[0], wx[1], wx[2]));
    return c;
}


/*
* get the 8 sub-boundingbox of the bbox from the middle point
*/
Bbox Bbox::getSBbox(const int &j){
    Point mid = midPoint();
    Bbox c = Bbox(mid);
    switch(j){
        case 0:
            c.extend(Point(vi[0], vi[1], vi[2]));
            break;
        case 1:
            c.extend(Point(vi[0], vi[1], vm[2]));
            break;
        case 2:
            c.extend(Point(vi[0], vm[1], vi[2]));
            break;
        case 3:
            c.extend(Point(vi[0], vm[1], vm[2]));
            break;
        case 4:
            c.extend(Point(vm[0], vi[1], vi[2]));
            break;
        case 5:
            c.extend(Point(vm[0], vi[1], vm[2]));
            break;
        case 6:
            c.extend(Point(vm[0], vm[1], vi[2]));
            break;
        case 7:
            c.extend(Point(vm[0], vm[1], vm[2]));
            break;
    }
    return c;
}

/*
* whether a ray intersect with a bounding box, solved on each dimension
*/
bool Bbox::hasIntersect(const Ray &r, float &t){
    Vector d = r.direction;
    Point p;
    t = Inf;
    float t1;

    // conduct ray-surface intersection on each dimension
    if (fabs(r.direction.x()) > eps){
        t1 = (vi[0] - r.origin.x()) / r.direction.x();
        p = r.calc(t1);
        if (p.y() >= vi[1] && p.y() <= vm[1] && p.z() >= vi[2] && p.z() <= vm[2])t = fmin(t, t1);
        t1 = (vm[0] - r.origin.x()) / r.direction.x();
        p = r.calc(t1);
        if (p.y() >= vi[1] && p.y() <= vm[1] && p.z() >= vi[2] && p.z() <= vm[2])t = fmin(t, t1);
    }
    if (fabs(r.direction.y()) > eps){
        t1 = (vi[1] - r.origin.y()) / r.direction.y();
        p = r.calc(t1);
        if (p.x() >= vi[0] && p.x() <= vm[0] && p.z() >= vi[2] && p.z() <= vm[2])t = fmin(t, t1);
        t1 = (vm[1] - r.origin.y()) / r.direction.y();
        p = r.calc(t1);
        if (p.x() >= vi[0] && p.x() <= vm[0] && p.z() >= vi[2] && p.z() <= vm[2])t = fmin(t, t1);
    }
    if (fabs(r.direction.z()) > eps){
        t1 = (vi[2] - r.origin.z()) / r.direction.z();
        p = r.calc(t1);
        if (p.x() >= vi[0] && p.x() <= vm[0] && p.y() >= vi[1] && p.y() <= vm[1])t = fmin(t, t1);
        t1 = (vm[2] - r.origin.z()) / r.direction.z();
        p = r.calc(t1);
        if (p.x() >= vi[0] && p.x() <= vm[0] && p.y() >= vi[1] && p.y() <= vm[1])t = fmin(t, t1);
    }

    return t < Inf;
}


/*
* Output the property of a Bbox for debugging.
*/
void Bbox::output(){
    printf("Bounding Box: x(%f,%f) y(%f,%f) z(%f,%f)\n", vi[0], vm[0], vi[1], vm[1], vi[2], vm[2]);
}