#include <object/environmentmap/lightprobe.h>
#include <cstdio>


/*
* Construct EnvMap from a .ppm file
*/
Lightprobe::Lightprobe(char *ch){
    FILE *file = fopen(ch, "r");
    char chs[6];
    int x, y, z, mx;
    fscanf(file, "%s", chs);
    fscanf(file, "%d %d", &widx, &widy);
    fscanf(file, "%d", &mx);
    cl = new Color*[widy + 2];
    for (int j = 0; j < widy; j++){
        cl[j] = new Color[widx + 2];
        for (unsigned int i = 0; i < widx; i++){
            fscanf(file, "%d%d%d", &x, &y, &z);
            cl[j][i] = Color(float(x) / mx, float(y) / mx, float(z) / mx);
        }
        fprintf(stderr, "\rReading EnvironmentMap %s %f%%", ch, 100.f * float(j + 1) / widy);
    }
    fprintf(stderr, "\n");
    fclose(file);
}

/*
* Destruction
*/
Lightprobe::~Lightprobe(){
    for(unsigned int i = 0; i < widy; i++) delete cl[i];
    delete[] cl;
}

/*
 * normalize a calculated projection to (-0.5, 0.5)
*/
float Lightprobe::normalize(const float &x){
    return 1.0f / (1.0f + exp(- 4.0f * x)) - 0.5f;
}

/*
* get the Color of envmap by direction
*/
Color Lightprobe::getColor(const Vector &d){
    if ((1.0f - d.z()) < eps) return Color(0.0f, 0.0f, 0.0f);
    float X = d.x() / (1.0f - d.z()), Y = d.y() / (1.0f - d.z());
    float len = sqrt(X * X + Y * Y), fps = normalize(len) / len * 0.95;
    X = X * fps + 0.5f;
    Y = Y * fps + 0.5f;
    int nx = X * (widx - 1), ny = Y * (widy - 1);
    return cl[nx][ny];
}