#include <object/scene.h>

/*
* Construct the scene
*/
Scene::Scene(){
    obj.clear();
    objs = 0;
    envmap = nullptr;
    medium = nullptr;
    wts = nullptr;
    prepd = false;
    eobj = nullptr;
}

/*
* add and get medium
*/
void Scene::addMedium(Medium *m){
    medium = m;
}

Medium* Scene::getMedium(){
    return medium;
}

/*
* add and get shapes
*/
void Scene::addShape(Shape *s){
    obj.push_back(s);
    objs++;
}

Shape* Scene::getShape(const int &k){
    return obj[k];
}

int Scene::getObjs(){
    return objs;
}

/*
* add and get envmap
*/
void Scene::addEnvmap(EnvironmentMap *env){
    envmap = env;
}

EnvironmentMap* Scene::getEnvmap(){
    return envmap;
}

/*
* Ray-Scene Intersection
*/
bool Scene::hasIntersection(const Ray &ray){
    float t;
    for (unsigned int i = 0; i < objs; i++)
        if(obj[i]->getBbox().hasIntersect(ray, t) && obj[i]->hasIntersection(ray)) return true;
    return false;
}

bool Scene::hasIntersection(const Ray &ray, Intersection& p){
    Intersection px;
    p.t = Inf;
    float t;
    for (unsigned int i = 0; i < objs; i++)
        if(obj[i]->getBbox().hasIntersect(ray, t) && t < p.t){
            bool tg = obj[i]->hasIntersection(ray, px);
            if (p.t > px.t && tg){
                p = px;
                p.obj = i;
            }
        }
    return p.t < Inf;
}

/*
* preparation before the rendering procedure
*/
void Scene::prep(){
    if (prepd) return;
    unsigned int semit = 0, ns = getObjs();
    eobj = new unsigned int[ns + 2];
    float *sobj = new float[ns + 2];
    for (unsigned int i = 0; i < ns; i++)
        if(getShape(i)->isEmit()){
            eobj[semit] = i;
            sobj[semit++] = getShape(i)->getArea();
        }
    if (semit > 0) wts = new WeightedSampler(semit, sobj);
    delete sobj;
}

/*
* sample a light source in the scene
*/
void Scene::samplelight(const Point &pi, Point &po, Normal &nn, Color &param, float &p){
    param = Color();
    if (wts != nullptr){
        SampleData xx = wts->sample();
        p = xx.Float * getShape(eobj[xx.uInt])->sample(po, nn);
        Vector d = po - pi, dn = d;
        float dis = d.length();
        Color ref(1.0f, 1.0f, 1.0f);
        dn.normalize();
        if (!hasIntersection(Ray(pi, dn, eps, dis - eps)))
            ref = getShape(eobj[xx.uInt])->getEmit() * fmax(0.0f, - 1.0f * nn * dn) / (dis * dis);
        param = ref;
    }
}

/*
* Find out whether light source exists
*/
bool Scene::hasLight(){
    return (wts != nullptr);
}