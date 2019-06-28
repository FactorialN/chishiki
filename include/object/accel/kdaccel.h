/*
k-d tree accel.
*/

#ifndef __OBJECT_ACCEL_KDACCEL_H__
#define __OBJECT_ACCEL_KDACCEL_H__

#include <object/accel/accel.h>

/*
* A Node on the KdTree (Actually Octree but conceptually the same)
*/
class KdAccelNode{
public:
    Bbox bbox;
    Triangle *tris;
    bool isLeaf;
    unsigned int ns;
    KdAccelNode *son[8];

    /*
    * Construction of a Node
    */
    KdAccelNode(Triangle *m, const unsigned int &n, const unsigned int &depth);

    /*
    * Intersection Method
    */
    bool hasIntersection(const Ray &ray);
    bool hasIntersection(const Ray &ray, Intersection& p);

    void putIn(std::vector<int>* ptn, const Point &pCur, const Point &pAno, const int &pICur, const int pIAno, bool uset, const float &threshold);
    void visitLeafAndBuild(std::vector<int>* ptn, const float &threshold);
};


/*
* KdAccel Class defines a class for KD tree Acceleration
*/
class KdAccel : public Accel{
private:
    KdAccelNode *rt;
public:

    KdAccel(Triangle *m, const int &n);
    ~KdAccel();

    /*
    * 2 methods to get the intersection
    */
    virtual bool hasIntersection(const Ray &ray);
    virtual bool hasIntersection(const Ray &ray, Intersection& p);

    // construct belonging pair vectors for simplification
    virtual void surfBuild(std::vector<int>* ptn, const float &threshold);
};

#endif