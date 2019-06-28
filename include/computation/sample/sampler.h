/*
* This is the base interface class for generating sample by a distribution.
*/

#ifndef __COMPUTATION_SAMPLE_SAMPLER_H__
#define __COMPUTATION_SAMPLE_SAMPLER_H__

#include <computation/linear/linearhead.h>
#include <algorithm>

/*
* This class is to save the data sampled
*/
struct SampleData{
    unsigned int uInt;
    float Float;
    Point p3;
    Point2f p2;
};

/*
* This class is the base class of All MathDistributionSampler and WeightedDistributionSampler
*/
class Sampler{
    /*
    * Actually there's nothing to implement here cause we don't need an abstract sampler.
    */
public:
    Sampler(){}
    virtual SampleData sample() = 0;
};

#endif