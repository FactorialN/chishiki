#include <computation/sample/weighted.h>


/*
* Construction from a given array.
*/
WeightedSampler::WeightedSampler(const unsigned int &m, float *a){
    n = m;
    pdf = new float[n+1];
    p = new float[n+1];
    ps = 0.0f;
    for (unsigned int i = 0; i < n; i++){
        pdf[i] = a[i];
        ps += a[i];
    }

    // Normalize the pdf function
    float inv_ps = 1.0f / ps;
    pdf[0] = p[0] = a[0] * inv_ps;
    for (unsigned int i = 1; i < n; i++){
        pdf[i] *= inv_ps;
        p[i] = p[i-1] + pdf[i];
    }
}

/*
* Sample a from the dataset
*/
SampleData WeightedSampler::sample(){
    float miu = drand48();
    SampleData val;
    for (unsigned int i = 0; i < n; i++)
        if (miu < p[i]){
            val.uInt = i;
            val.Float = pdf[i];
            break;
        }
    return val;
}

/*
* Weighted Sampler Destruction
*/
WeightedSampler::~WeightedSampler(){
    delete[] pdf;
    delete[] p;
}