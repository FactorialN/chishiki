#include <interface/camera/film.h>
#include <cstdio>

Film::Film(const int &x, const int &y){
    widx = x;
    widy = y;
    cl = new Color*[x];
    for (unsigned int i = 0; i < x; i++) {
        cl[i] = new Color[y];
        for (unsigned int j = 0; j < y; j++) cl[i][j] = Color(0.0f, 0.0f, 0.0f);
    }
}

void Film::addColor(const int &x, const int &y, const Color &c){
    cl[x][y] = cl[x][y] + c;
}

void Film::output(FILE *f){
    fprintf(f, "P3\n");
    fprintf(f, "%d %d\n", widx, widy);
    fprintf(f, "255\n");
    for (unsigned int i = 0; i < widx; i++){
        for (unsigned int j = 0; j < widy; j++) {
            int x = int(fmin(cl[i][j].x(), 1.0f) * 255);
            int y = int(fmin(cl[i][j].y(), 1.0f) * 255);
            int z = int(fmin(cl[i][j].z(), 1.0f) * 255);
            fprintf(f, "%d %d %d ", x, y, z);
        }
        fprintf(f, "\n");
    }
}