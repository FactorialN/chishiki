/*
* This header file defined 2 base class of homo linear values used in other classes.
*/

#ifndef __COMPUTATION_LINEAR_HOMO_H__
#define __COMPUTATION_LINEAR_HOMO_H__

#include <cmath>

/*
* A class of HomoVectors, act as the base class for points, vectors and normals.
*/
class HomoVector{
public:

    /*
    * The only construction function of a 4-d HomoVector.
    */
    HomoVector(){v[0] = v[1] = v[2] = v[3] = 0;}
    HomoVector(const float &x, const float &y, const float &z, const float &k){
        v[0] = x; v[1] = y; v[2] = z; v[3] = k;
    }

    /*
    * A method to visit all the value in the vector.
    */
    inline float x()const{return v[0];}
    inline float y()const{return v[1];}
    inline float z()const{return v[2];}
    inline float k()const{return v[3];}
    inline float val(unsigned int k)const{return v[k];}

    /*
    * Some basic operations to all vectors and normals.
    */
    inline float length()const{return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);}
    inline float normalize(){
        float len = length();
        v[0] /= len; v[1] /= len; v[2] /= len;
        return len;
    }
    inline float max()const{return v[0]>v[1]?(v[2]>v[0]?v[2]:v[0]):(v[2]>v[1]?v[2]:v[1]);}
    inline float min()const{return v[0]<v[1]?(v[2]<v[0]?v[2]:v[0]):(v[2]<v[1]?v[2]:v[1]);}
    inline void permute(unsigned int i, unsigned int j, unsigned int k){
        float cur[]={v[i], v[j], v[k]};
        v[0]=cur[0];v[1]=cur[1];v[2]=cur[2];
    }
    inline HomoVector vecAbs()const{
        return HomoVector(fabs(v[0]), fabs(v[1]), fabs(v[2]), fabs(v[3]));
    }
    HomoVector multi(const HomoVector &b)const{
        return HomoVector(v[0] * b.val(0), v[1] * b.val(1), v[2] * b.val(2), 0.0f);
    }
private:

    /*
    * The coordinate value on each dimension of the vector.
    */
    float v[4];

};

/*
* The defination of basic Vector calculation
*/
HomoVector operator*(const HomoVector &a, const float &b);
HomoVector operator*(const float &b, const HomoVector &a);
HomoVector operator/(const HomoVector &a, const float &b);
HomoVector operator+(const HomoVector &a, const HomoVector &b);
HomoVector operator-(const HomoVector &a, const HomoVector &b);
float operator*(const HomoVector &a, const HomoVector &b);
HomoVector operator%(const HomoVector &a, const HomoVector &b);

/*
* A base class for Matrix computation, act as the base class for transformations.
*/
class HomoMatrix{
public:

    /*
    * Default construction.
    */
    HomoMatrix(){
        for (unsigned int i = 0; i < 4; i++)
            for (unsigned int j = 0; j < 4; j++)
                v[i][j] = 0;
    }

    /*
    * Construction function from all the parameters.
    */
    HomoMatrix(const float x[4][4]){
        for (unsigned int i = 0; i < 4; i++)
            for (unsigned int j = 0; j < 4; j++)
                v[i][j] = x[i][j];
    }
    HomoMatrix(const float &a11, const float &a12, const float &a13, const float &a14,
               const float &a21, const float &a22, const float &a23, const float &a24,
               const float &a31, const float &a32, const float &a33, const float &a34,
               const float &a41, const float &a42, const float &a43, const float &a44){
        v[0][0] = a11; v[0][1] = a12; v[0][2] = a13; v[0][3]= a14;
        v[1][0] = a21; v[1][1] = a22; v[1][2] = a23; v[1][3]= a24;
        v[2][0] = a31; v[2][1] = a32; v[2][2] = a33; v[2][3]= a34;
        v[3][0] = a41; v[3][1] = a42; v[3][2] = a43; v[3][3]= a44;
    }

    /*
    * Modification to HomoMatrix
    */
    void Modify(const float x[4][4]){
        for (unsigned int i = 0; i < 4; i++)
            for (unsigned int j = 0; j < 4; j++)
                v[i][j] = x[i][j];
    }

    HomoMatrix operator+(const HomoMatrix &b);

    /*
    * Matrix multiply operation.
    */
    HomoMatrix operator*(const HomoMatrix &b)const;
    HomoVector operator*(const HomoVector &b)const;

    /*
    * Basic Matrix calculations.
    */
    HomoMatrix transpose();
    HomoMatrix reverse();

    inline float val(const int &x, const int &y)const{return v[x - 1][y - 1];}
    
private:

    /*
    * The value on each position of the 4*4 matrix.
    */
    float v[4][4];
};

#endif