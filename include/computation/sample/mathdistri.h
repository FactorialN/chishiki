/*
* Several samplers according to mathematical distributions are implemented here.
*/

#ifndef __COMPUTATION_SAMPLE_MATHDISTRI_H__
#define __COMPUTATION_SAMPLE_MATHDISTRI_H__

#include <computation/sample/sampler.h>

class SquareSampler : public Sampler{
public:
    /*
    * The Construction of MathSampler is very trivial, with no parameters.
    */
   SquareSampler():Sampler(){}
   SampleData sample();
};

class TentSampler : public Sampler{
public:
    /*
    * The Construction of MathSampler is very trivial, with no parameters.
    */
   TentSampler():Sampler(){}
   SampleData sample();
};

class UniformDiskSampler : public Sampler{
public:
    /*
    * The Construction of MathSampler is very trivial, with no parameters.
    */
   UniformDiskSampler():Sampler(){}
   SampleData sample();
};

class UniformSphereSampler : public Sampler{
public:
    /*
    * The Construction of MathSampler is very trivial, with no parameters.
    */
   UniformSphereSampler():Sampler(){}
   SampleData sample();
};

class UniformHemiSphereSampler : public Sampler{
public:
    /*
    * The Construction of MathSampler is very trivial, with no parameters.
    */
   UniformHemiSphereSampler():Sampler(){}
   SampleData sample();
};

class UniformCosineSphereSampler : public Sampler{
public:
    /*
    * The Construction of MathSampler is very trivial, with no parameters.
    */
   UniformCosineSphereSampler():Sampler(){}
   SampleData sample();
};

class BeckmannSampler : public Sampler{
public:
    /*
    * The Construction of MathSampler is very trivial, with no parameters.
    */
   BeckmannSampler():Sampler(){}
   SampleData sample();
   SampleData sample(const float &alpha);
   virtual float pdf(const float &alpha, const Vector &v);
   ~BeckmannSampler(){}
};

#endif