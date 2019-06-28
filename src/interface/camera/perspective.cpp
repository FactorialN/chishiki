#include <interface/camera/perspective.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <future>
#include <vector>

PerspectiveCamera::PerspectiveCamera(const Point &v, const Point &l, const Vector &u, const int &x, const int &y, const int &sps, const float &ff){
    film = new Film(x, y);
    viewPoint = v;
    lookatPoint = l;
    inVec = -1.0f * Normal(u);
    direcVec = Normal(l - v);
    xVec = -1.0f * Normal(direcVec % inVec);
    widx = x;
    widy = y;
    nSamples = sps;
    k = float(widx) / float(widy);
    revsp = 1.0f / nSamples;
    f = ff;
}

void PerspectiveCamera::conduct(const int &x, const int &y, Scene *scene){
    float u, v;
    for (unsigned int s = 0; s < nSamples; s++){
        SampleData sp = sampler->sample();
        u = ((x + sp.p2.a) / float(widx) - 0.5f) * f;
        v = ((y + sp.p2.b) / float(widy) - 0.5f) * f;
        Normal direc = Normal(k * v * xVec + u * inVec + direcVec);
        Color cl = render->Lo(scene, Ray(viewPoint, direc));
        film->addColor(x, y, cl * revsp);
    }
}

void PerspectiveCamera::shot(Scene *scene){
    sampler = new SquareSampler();
    long t = clock();
    auto start = std::chrono::system_clock::now();
    std::vector<std::thread> v;
    int xx[widx + 5], yy[widy + 5];
    for (int y = widy - 1; y >= 0; y--){
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        fprintf(stderr, "\rChishiki Rendering %5.4f%% for %.2f seconds", 100.0f - 100.0f * y / (widy - 1), float(duration.count()) / 1000000.f); 
        yy[y] = y;
        for (int x = 0; x < widx; x++){
            xx[x] = x;
            v.emplace_back(&PerspectiveCamera::conduct, *this, std::cref(xx[x]), std::cref(yy[y]), scene);
        }
    }
    for (auto &t : v)
        if (t.joinable()) t.join();
    fprintf(stderr, "\n");
}
 
void PerspectiveCamera::output(FILE *p){
    film->output(p);
}