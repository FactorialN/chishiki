#include <object/shape/sphere.h>

/*
* Construct the sphere
*/
Sphere::Sphere(const Point &cen, const float &rad){
    centre = cen;
    radius = rad;
    bbox = Bbox(Point(cen.x() - rad, cen.y() - rad, cen.z() - rad), Point(cen.x() + rad, cen.y() + rad, cen.z() + rad));
}

/*
* Ray-Sphere Intersection
*/
bool Sphere::hasIntersection(const Ray &ray){
    Vector OmC = ray.Origin() - centre;
    float A = ray.Direction() * ray.Direction(), B = 2.0f * ray.Direction() * OmC, C = OmC * OmC - radius * radius;
    float Delta = B * B - 4.0f * A * C;
    if (Delta < 0) return false;
    Delta = sqrt(Delta);
    float t1 = (- B - Delta) / (2.0f * A), t2 = (- B + Delta) / (2.0f * A);
    float t = t1 > 0 ? t1 : t2;
    if (t > ray.tmax || t < ray.tmin)return false;
    return true;
}

bool Sphere::hasIntersection(const Ray &ray, Intersection& p){
    p.t = Inf;
    Vector OmC = ray.Origin() - centre;
    float A = ray.Direction() * ray.Direction(), B = 2.0f * ray.Direction() * OmC, C = OmC * OmC - radius * radius;
    float Delta = B * B - 4.0f * A * C;
    if (Delta < 0) return false;
    Delta = sqrt(Delta);
    float t1 = (- B - Delta) / (2.0f * A), t2 = (- B + Delta) / (2.0f * A);
    float t = t1 > 0 ? t1 : t2;
    if (t > ray.tmax || t < ray.tmin)return false;
    p.p = ray.calc(t);
    p.n = Normal(p.p - centre);
    p.t = t;
    return true;
}

/*
* Calculate the bbox of a sphere
*/
Bbox Sphere::getBbox(){
    return bbox;
}

/*
* Calculate the area of a sphere
*/
float Sphere::getArea(){
    return 4 * PI * radius * radius;
}

/*
* sample a point on the area
*/
float Sphere::sample(Point &p, Normal &n){
    Sampler *sample = new UniformSphereSampler();
    n = Normal(sample->sample().p3);
    p = Vector(n) * radius + centre;
    delete sample;
    return 0.25f / (PI * radius * radius);
}