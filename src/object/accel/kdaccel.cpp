#include <object/accel/kdaccel.h>
#include <utility>
#include <algorithm>

/*
* Construction of KD tree Node
*/
KdAccelNode::KdAccelNode(Triangle *m, const unsigned int &n, const unsigned int &depth){
    if(n <= 10 || depth > 50){
        // To deep or few triangles
        tris = new Triangle[n + 5];
        for (unsigned int i = 0; i < n; i++) tris[i] = Triangle(m[i]);
        isLeaf = true;
        ns = n;
        bbox = m[0].getBbox();
        for (unsigned int i = 1; i < n; i++) bbox.extend(m[i].getBbox());
        for (unsigned int i = 0; i < 8; i++) son[i] = nullptr;
    }
    else{
        tris = nullptr;
        isLeaf = false;
        ns = n;
        bbox = m[0].getBbox();
        bool vst[n + 5];
        vst[0] = false;
        for (unsigned int i = 1; i < n; i++){
            bbox.extend(m[i].getBbox());
            vst[i] = false;
        }
        for (unsigned int i = 0; i < 8; i++){
            int sm = 0;
            Triangle *ms = new Triangle[n + 5];
            Bbox sbbox = bbox.getSBbox(i);
            // add to branch if bbox intersects
            for (unsigned int j = 0; j < n; j++)
                if(sbbox.hasIntersect(m[j].getBbox()) && !vst[j]){
                    // split the triangles to each son with no duplicate
                    ms[sm++] = Triangle(m[j]);
                    vst[j] = true;
                }
            if (sm > 0)son[i] = new KdAccelNode(ms, sm, depth + 1);
            else son[i] = nullptr;
            delete[] ms;
        }
    }
}

/*
* Ra-treeNode intersection
*/
bool KdAccelNode::hasIntersection(const Ray &ray){
    Intersection p;
    if (isLeaf){
        for (unsigned int i = 0; i < ns; i++)
            if (tris[i].hasIntersection(ray, p))return true;
        return false;
    }
    else{
        float t;
        // go to the sons in order of distance
        std::pair<float, unsigned int> a[10];
        for (unsigned int i = 0; i < 8; i++){
            a[i] = std::pair<float, unsigned int>(Inf, i);
            if (son[i] != nullptr && son[i]->bbox.hasIntersect(ray, t)) a[i].first = t;
        }
        sort(a, a + 8);
        for (unsigned int i = 0; i < 8; i++)
            if (son[a[i].second] != nullptr && a[i].first < Inf && son[a[i].second]->hasIntersection(ray))return true;
        return false;
    }
}

bool KdAccelNode::hasIntersection(const Ray &ray, Intersection& p){
    p.t = Inf;
    Intersection px;
    if (isLeaf){     
        for (unsigned int i = 0; i < ns; i++){
            bool tg = tris[i].hasIntersection(ray, px);
            if (px.t < p.t && tg) p = px;
        }
        return p.t < Inf;
    }
    else{
        float t;
        // go to the sons in order of distance
        std::pair<float, unsigned int> a[10];
        for (unsigned int i = 0; i < 8; i++){
            a[i] = std::pair<float, unsigned int>(Inf, i);
            if (son[i] != nullptr && son[i]->bbox.hasIntersect(ray, t)) a[i].first = t;
        }
        sort(a, a + 8);
        for (unsigned int i = 0; i < 8; i++)
            if (son[a[i].second] != nullptr && a[i].first < p.t){
                bool tg = son[a[i].second]->hasIntersection(ray, px);
                if (px.t < p.t && tg) p = px;
            }
        return p.t < Inf;
    }
}

void KdAccelNode::putIn(std::vector<int>* ptn, const Point &pCur, const Point &pAno, const int &pICur, const int pIAno, bool uset, const float &threshold){
    bool tg = false;
    if ((!uset) || (pCur-pAno).length() < threshold){
        for (unsigned int k = 0; k < ptn[pICur].size(); k++)
            if (ptn[pICur][k] == pIAno) tg = true;
        if (!tg){
            ptn[pICur].push_back(pIAno);
            ptn[pIAno].push_back(pICur);
        }
    }

}

void KdAccelNode::visitLeafAndBuild(std::vector<int>* ptn, const float &threshold){
    if (isLeaf){
        for (unsigned int i = 0; i < ns; i++){
            Point A, B, C;
            int pA, pB, pC;
            
            tris[i].getPoints(A, B, C, pA, pB, pC);

            putIn(ptn, A, B, pA, pB, false, threshold);
            putIn(ptn, A, C, pA, pC, false, threshold);
            putIn(ptn, B, C, pB, pC, false, threshold);

            for (unsigned int j = i + 1; j < ns; j++){
                Point D, E, F;
                int pD, pE, pF;
                
                tris[i].getPoints(D, E, F, pD, pE, pF);

                putIn(ptn, A, D, pA, pD, true, threshold);
                putIn(ptn, A, E, pA, pE, true, threshold);
                putIn(ptn, A, F, pA, pF, true, threshold);
                putIn(ptn, B, D, pB, pD, true, threshold);
                putIn(ptn, B, E, pB, pE, true, threshold);
                putIn(ptn, B, F, pB, pF, true, threshold);
                putIn(ptn, C, D, pC, pD, true, threshold);
                putIn(ptn, C, E, pC, pE, true, threshold);
                putIn(ptn, C, F, pC, pF, true, threshold);
            }
        }
        return;
    }
    else{
        for (unsigned int i = 0; i < 8; i++)
            if(son[i] != nullptr)
                son[i]->visitLeafAndBuild(ptn, threshold);
    }
}

/*
* construction of the tree.
*/
KdAccel::KdAccel(Triangle *m, const int &n){
    rt = new KdAccelNode(m, n, 1);
}

/*
* destructor
*/
KdAccel::~KdAccel(){
    delete rt;
    rt = nullptr;
}


/*
* Methods for ray-trianglemesh intersection
*/

bool KdAccel::hasIntersection(const Ray &ray){
    return rt->hasIntersection(ray);
}

bool KdAccel::hasIntersection(const Ray &ray, Intersection& p){
    return rt->hasIntersection(ray, p);
}


void KdAccel::surfBuild(std::vector<int>* ptn, const float &threshold){
    rt->visitLeafAndBuild(ptn, threshold);
}