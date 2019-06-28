#include <interface/analyse.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

Analyse::Analyse(char *fn){
    filename = fn;
    fprintf(stderr, "Analysing file %s\n", fn);
    std::ifstream file(filename);
    std::string linestr;
    scene = new Scene();
    while (std::getline(file, linestr)){
        std::string pref;
        std::istringstream line(linestr);
        line >> pref;
        if (pref == "EnvironmentMap") {
            line >> pref;
            if (pref == "Lightprobe"){
                line >> pref;
                char *ch = const_cast<char*>(pref.c_str());
                scene->addEnvmap(new Lightprobe(ch));
            }
        }
        else if (pref == "Object") {
            line >> pref;
            Shape *shape;
            if (pref == "Sphere") {
                float x, y, z, r;
                line >> x >> y >> z >> r;
                shape = new Sphere(Point(x, y, z), r);
            }
            else if (pref == "TriangleMesh") {
                line >> pref;
                char *ch = const_cast<char*>(pref.c_str());
                shape = new TriangleMesh(ch);
            }
            BSDF *bsdf;
            BSSRDF *bssrdf;
            Color Emit;
            bool isEmit = false, isBSSRDF = false;
            line >> pref;
            if (pref == "Microfacet") {
                float x, y, z, r;
                line >> x >> y >> z >> r;
                bsdf = new Microfacet(Color(x, y, z), r);
            }
            else if (pref == "Dielectric"){
                float x, y, z, r;
                line >> x >> y >> z >> r;
                bsdf = new Dielectric(Color(x, y, z), r);
            }
            else if (pref == "Diffuse"){
                float x, y, z;
                line >> x >> y >> z;
                bsdf = new Diffuse(Color(x, y, z));
            }
            else if (pref == "Mirror"){
                float x, y, z;
                line >> x >> y >> z;
                bsdf = new Mirror(Color(x, y, z));
            }
            else if (pref == "Emit"){
                float x, y, z;
                line >> x >> y >> z;
                Emit = Color(x, y, z);
                isEmit = true;
            }
            else if (pref == "Seperable"){
                float x, y;
                line >> x >> y;
                bssrdf = new SeperableBSSRDF(x, y);
                isBSSRDF = true;
            }

            if (isEmit) shape->addEmit(Emit);
            else if (isBSSRDF) shape->addBSSRDF(bssrdf);
            else shape->addBSDF(bsdf);
            scene->addShape(shape);
        }
        else if (pref == "Camera"){
            line >> pref;
            if (pref == "Perspective"){
                char ch;
                float x1, y1, z1;
                float x2, y2, z2;
                float x3, y3, z3;
                line >> ch >> x1 >> y1 >> z1 >> ch >> ch >> x2 >> y2 >> z2 >> ch >> ch >> x3 >> y3 >> z3 >> ch;
                int widx, widy, ssps, thrs;
                line >> widx >> widy >> ssps;
                float rr;
                line >> rr;
                camera = new PerspectiveCamera(Point(x1, y1, z1), Point(x2, y2, z2), Normal(x3, y3, z3), widx, widy, ssps, rr);
            }
        }
        else if (pref == "Render"){
            line >> pref;
            if (pref == "Whitted") camera->addInt(new WhittedIntegrator());
            else if (pref == "Normal") camera->addInt(new NormalIntegrator());
            else if (pref == "Ao") camera->addInt(new AoIntegrator());
            else if (pref == "Rt") camera->addInt(new RtIntegrator());
            else if (pref == "Volume") camera->addInt(new VolIntegrator());
        }
        else if (pref == "Medium"){
            line >> pref;
            if (pref == "Homogeneous") {
                float x, y;
                line >> x >> y;
                scene->addMedium(new HomoMedium(x, y));
            }
        }
        else if (pref == "Simplify"){
            isSimplify = true;
            float x;
            int y;
            line >> pref >> x >> y;
            Shape *shape;
            char *ch = const_cast<char*>(pref.c_str());
            shape = new TriangleMesh(ch);
            shape->simplify(x, y);
        }
    }
    if (!isSimplify) scene->prep();
}

void Analyse::run(){
    if (!isSimplify){
        camera->shot(scene);
        FILE *fp = fopen("cam.ppm", "w");
        camera->output(fp);
        fclose(fp);
    }
}