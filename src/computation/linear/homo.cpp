#include <computation/linear/homo.h>

HomoMatrix HomoMatrix::operator+(const HomoMatrix &b){
    float d[4][4] = {0};
    for (unsigned int i = 0; i < 4; i++)
        for (unsigned int j = 0; j < 4; j++)
                d[i][j] = v[i][j] + b.v[i][j];
    HomoMatrix c(d);
    return c;
}

HomoMatrix HomoMatrix::operator*(const HomoMatrix &b){
    float d[4][4] = {0};
    for (unsigned int i = 0; i < 4; i++)
        for (unsigned int j = 0; j < 4; j++)
            for (unsigned int k = 0; k < 4; k++)
                d[i][j] += v[i][k] * b.v[k][j];
    HomoMatrix c(d);
    return c;
}

HomoVector HomoMatrix::operator*(const HomoVector &b){
    float d[4] = {0};
    for (unsigned int i = 0; i < 4; i++)
        d[i] += v[i][0] * b.x() + v[i][1] * b.y() + v[i][2] * b.z() + v[i][3] * b.k();
    HomoVector c(d[0], d[1], d[2], d[3]);
    return c;
}

HomoMatrix HomoMatrix::transpose(){
    float d[4][4]={0};
    for (unsigned int i = 0; i < 4; i++)
        for (unsigned int j = 0; j < 4; j++)
            d[i][j] = v[j][i];
    HomoMatrix c(d);
    return c;
}

HomoMatrix HomoMatrix::reverse(){
    float d[4][4]={0};
    // TO DO
}

HomoVector operator*(const HomoVector &a, const float &b){
    return HomoVector(a.x() * b, a.y() * b, a.z() * b, a.k());
}
HomoVector operator*(const float &b, const HomoVector &a){
    return HomoVector(a.x() * b, a.y() * b, a.z() * b, a.k());
}
HomoVector operator/(const HomoVector &a, const float &b){
    return HomoVector(a.x() / b, a.y() / b, a.z() / b, a.k());
}
HomoVector operator+(const HomoVector &a, const HomoVector &b){
    return HomoVector(a.x() + b.x(), a.y() + b.y(), a.z() + b.z(), a.k() + b.k());
}
HomoVector operator-(const HomoVector &a, const HomoVector &b){
    return HomoVector(a.x() - b.x(), a.y() - b.y(), a.z() - b.z(), a.k() - b.k());
}
float operator*(const HomoVector &a, const HomoVector &b){
    return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}
HomoVector operator%(const HomoVector &a, const HomoVector &b){
    return HomoVector(a.y() * b.z() - a.z() * b.y(), a.z() * b.x() - a.x() * b.z(), a.x() * b.y() - a.y() * b.x(), 0.0);
}