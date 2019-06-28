/*
* A method to Sample by a given weight
*/

#ifndef __COMPUTATION_SAMPLE_WEIGHTED_H__
#define __COMPUTATION_SAMPLE_WEIGHTED_H__

#include <computation/sample/sampler.h>

/*
* WeightedSampler samples data by weight from a given array
*/
class WeightedSampler : public Sampler{
public:
    /*
    * Construction of the WeightedSampler with an array
    */
   WeightedSampler():Sampler(){n = 0;}
   WeightedSampler(const unsigned int &m, float *a);

   /*
   * Destruction
   */
  ~WeightedSampler();

   /*
   * Realization of the sample here.
   */
   virtual SampleData sample();
private:
    float *pdf, *p, ps;
    unsigned int n;
};

#endif