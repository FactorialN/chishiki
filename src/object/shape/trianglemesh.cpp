#include <object/shape/trianglemesh.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

/*
* Assistance function for parsing faces
*/
void TriangleMesh::decode(const std::string& s, unsigned int &a, unsigned int &b){
    std::vector<int> tokens;
    tokens.clear();
    unsigned int j = -1;
    for (unsigned int i = 0; i < s.length(); i++){
        if (i == 0 || s[i] == '/') {
            tokens.push_back(0);
            j++;
        }
        if (s[i] >= '0' && s[i] <= '9') tokens[j] = tokens[j] * 10 + s[i] - '0';
    }
    a = tokens[0];
    b = tokens[2];
}

/*
* Construct the TriangleMesh from a .obj file
*/
TriangleMesh::TriangleMesh(char *fn){

    // This part is according to nori
    fprintf(stderr, "Constructing TriangleMesh %s\n", fn);
    std::ifstream file(fn);
    std::string linestr;
    std::vector<Point>points;
    std::vector<Normal>pnormals;
    std::vector<Triangle>triangles;
    float x, y, z;
    points.clear();
    pnormals.clear();
    triangles.clear();
    points.push_back(Point());
    pnormals.push_back(Normal());

    // parsing .obj file
    while (std::getline(file, linestr)){
        std::string pref;
        std::istringstream line(linestr);
        line >> pref;
        if(pref == "v"){
            line >> x >> y >> z;
            points.push_back(Point(x, y, z));
        }
        else if(pref == "vn"){
            line >> x >> y >> z;
            pnormals.push_back(Normal(x, y, z));
        }
        else if(pref == "vt"){
            line >> x >> y;
        }
        else if(pref == "f"){
            std::string x, y, z, t;
            line >> x >> y >> z >> t;
            unsigned int x1, x2, y1, y2, z1, z2, t1, t2;
            if (t.empty()) {
                decode(x, x1, x2);
                decode(y, y1, y2);
                decode(z, z1, z2);
                if (x2 && y2 && z2) triangles.push_back(Triangle(points[x1], points[y1], points[z1], pnormals[x2], pnormals[y2], pnormals[z2], x1, y1, z1));
                else triangles.push_back(Triangle(points[x1], points[y1], points[z1], x1, y1, z1));
            }
            else{
                decode(x, x1, x2);
                decode(y, y1, y2);
                decode(z, z1, z2);
                decode(t, t1, t2);
                if (x2 && y2 && z2 && t2){
                    triangles.push_back(Triangle(points[x1], points[y1], points[z1], pnormals[x2], pnormals[y2], pnormals[z2], x1, y1, z1));
                    triangles.push_back(Triangle(points[z1], points[t1], points[x1], pnormals[z2], pnormals[t2], pnormals[x2], z1, t1, x1));
                }
                else{
                    triangles.push_back(Triangle(points[x1], points[y1], points[z1], x1, y1, z1));
                    triangles.push_back(Triangle(points[z1], points[t1], points[x1], z1, t1, x1));
                }
            }
        }
    }

    // conduct basic calculations
    nmesh = triangles.size();
    npoints = points.size();
    meshes = new Triangle[nmesh + 2];
    ppoints = new Point[npoints + 2];
    area = 0.0f;
    float *ara = new float[nmesh + 2];
    for (unsigned int i = 0; i < npoints; i++) ppoints[i] = points[i];
    for (unsigned int i = 0; i < nmesh; i++){
        meshes[i] = triangles[i];
        ara[i] = meshes[i].getArea();
        area += ara[i];
        bbox.extend(triangles[i].getBbox());
    }
    wts = new WeightedSampler(nmesh, ara);
    a = new KdAccel(meshes, nmesh);
    delete[] ara;
}

/*
* Ray-Triangle Mesh Intersection.
*/
bool TriangleMesh::hasIntersection(const Ray &ray){
    return a->hasIntersection(ray);
}

bool TriangleMesh::hasIntersection(const Ray &ray, Intersection& p){
    return a->hasIntersection(ray, p);
}

/*
* find the bounding box of the triangle mesh
*/
Bbox TriangleMesh::getBbox(){
    return bbox;
}

/*
* find the area of the triangle mesh object
*/
float TriangleMesh::getArea(){
    return area;
}

/*
* sample a point from the triangle mesh
*/
float TriangleMesh::sample(Point &p, Normal &n){
    SampleData x = wts->sample();
    p = meshes[x.uInt].sample(n);
    return x.Float;
}

int getf(int x, unsigned int *prt){
    if (prt[x] == x) return x;
    prt[x] = getf(prt[x], prt);
    return prt[x];
}

/*
* simplify using quadric error metrics
*/
void TriangleMesh::simplify(const float &threshold, const int &pointsLeft){
    std::priority_queue<SimplifyCompare> q;
    std::vector<int> *ptn = new std::vector<int>[npoints * 2];
    unsigned int *pointBelong = new unsigned int[npoints * 2];
    unsigned int *pointMap = new unsigned int[npoints * 2];
    HomoMatrix *pointQ = new HomoMatrix[npoints * 2];
    Point *points = new Point[npoints * 2];
    unsigned int tot = npoints - 1;
    for (unsigned int i = 0; i < npoints * 2; i++) {
        if (i <= tot) points[i] = ppoints[i];
        pointBelong[i] = i;
        ptn[i].clear();
    }
    for (unsigned int i = 0; i < nmesh; i++) {
        HomoVector q = meshes[i].surfaceEqua();
        HomoMatrix Q = HomoMatrix(q.x()*q.x(), q.x()*q.y(), q.x()*q.z(), q.x()*q.k(),
                                  q.y()*q.x(), q.y()*q.y(), q.y()*q.z(), q.y()*q.k(),
                                  q.z()*q.x(), q.z()*q.y(), q.z()*q.z(), q.z()*q.k(),
                                  q.k()*q.x(), q.k()*q.y(), q.k()*q.z(), q.k()*q.k());
        Point A, B, C;
        int pA, pB, pC;
        meshes[i].getPoints(A, B, C, pA, pB, pC);
        pointQ[pA] = pointQ[pA] + Q;
        pointQ[pB] = pointQ[pB] + Q;
        pointQ[pC] = pointQ[pC] + Q;
    }
    a->surfBuild(ptn, threshold);
    for (unsigned int i = 1; i <= tot; i++)
        for (unsigned int j = 0; j < ptn[i].size(); j++){
            Point md = Point(0.5*(points[i].x()+points[ptn[i][j]].x()), 0.5*(points[i].y()+points[ptn[i][j]].y()), 0.5*(points[i].z()+points[ptn[i][j]].z()));
            if(i < ptn[i][j])q.push(SimplifyCompare(i, ptn[i][j], md, (points[i]-points[ptn[i][j]]).length()));
        }
    unsigned int epcs = npoints - pointsLeft;
    if (npoints < pointsLeft) epcs = 0;
    for (unsigned int ep = 0; ep < epcs; ep++){
        SimplifyCompare tp = q.top(); q.pop();
        while(getf(tp.A, pointBelong) != tp.A || getf(tp.B, pointBelong) != tp.B){tp = q.top(); q.pop();}
        points[++tot] = tp.C;
        for (unsigned int j = 0; j < ptn[tp.A].size(); j++){
            int k = getf(ptn[tp.A][j], pointBelong);
            ptn[tot].push_back(k);
            Point md = Point(0.5*(tp.C.x()+points[k].x()), 0.5*(tp.C.y()+points[k].y()), 0.5*(tp.C.z()+points[k].z()));
            q.push(SimplifyCompare(tot, k, md, (tp.C-points[k]).length()));
        }
        for (unsigned int j = 0; j < ptn[tp.B].size(); j++){
            int k = getf(ptn[tp.B][j], pointBelong);
            ptn[tot].push_back(k);
            Point md = Point(0.5*(tp.C.x()+points[k].x()), 0.5*(tp.C.y()+points[k].y()), 0.5*(tp.C.z()+points[k].z()));
            q.push(SimplifyCompare(tot, k, md, (tp.C-points[k]).length()));
        }
        pointBelong[tp.A] = pointBelong[tp.B] = tot;
    }
    
    FILE *f = fopen("simplified.obj", "w");
    pointMap[0] = 0;
    for (unsigned int i = 1; i <= tot; i++){
        pointMap[i] = pointMap[i-1];
        if (getf(i, pointBelong)==i){
            pointMap[i]++;
            fprintf(f, "v %f %f %f\n", points[i].x(), points[i].y(), points[i].z());
        }
    }
    for (unsigned int i = 0; i < nmesh; i++){
        Point A, B, C;
        int pA, pB, pC;
        meshes[i].getPoints(A, B, C, pA, pB, pC);
        pA = pointMap[getf(pA, pointBelong)];
        pB = pointMap[getf(pB, pointBelong)];
        pC = pointMap[getf(pC, pointBelong)];
        if (pA != pB && pA != pC && pB != pC)
            fprintf(f, "f %d %d %d\n", pA, pB, pC);
    }
    fclose(f);

    delete[] pointBelong;
}