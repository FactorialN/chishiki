#include <computation/sample/mathdistri.h>

SampleData SquareSampler::sample(){
    SampleData x;
    x.p2.a = drand48();
    x.p2.b = drand48();
    return x;
}

SampleData TentSampler::sample(){
    // TO DO
}

SampleData UniformDiskSampler::sample(){
    // TO DO
}

SampleData UniformSphereSampler::sample(){
    float x = drand48(), y = drand48();
    float r = sqrt(1 - (2 * x - 1) * (2 * x - 1)), phi = 2 * PI * y;
    SampleData xx;
    xx.p3 = Vector(r * cos(phi), r * sin(phi), 2 * x - 1);
    return xx;
}

SampleData UniformHemiSphereSampler::sample(){
    float x = drand48(), y = drand48();
    float r = sqrt(1 - (2 * x - 1) * (2 * x - 1)), phi = 2 * PI * y;
    SampleData xx;
    xx.p3 = Vector(r * cos(phi), r * sin(phi), fabs(2 * x - 1));
    return xx;
}

SampleData UniformCosineSphereSampler::sample(){
    SampleData x;
    float r = drand48();
    float phi = drand48() * PI * 2.0f;
    x.p3 = Point(r * cos(phi), r * sin(phi), sqrt(1 - r * r));
    return x;
}

SampleData BeckmannSampler::sample(){
    // TO DO throw warnings
}

SampleData BeckmannSampler::sample(const float &alpha){
    float cth, sth;
    float x = drand48(), y = drand48();
    if (y == 1.0f)cth = 0.0f;
    else {
        float t1 = log(1 - y) * alpha * alpha;
        t1 = 1 - t1;
        cth = sqrt(1.0f / t1);
    }
    float phi = 2.0f * PI * x;
    sth = sqrt(1 - cth * cth);
    SampleData xx;
    xx.p3 = Vector(sth * cos(phi), sth * sin(phi), cth);
    return xx;
}

float BeckmannSampler::pdf(const float &alpha, const Vector &v){
    float theta = acos(v.z());
    float d = 0.5f / PI;
    float t1 = tan(theta) / alpha;
    float t2 = cos(theta);
    d *= 2.0f * exp(-t1 * t1);
    d /= alpha * alpha * t2 * t2 * t2;
    return d;
}