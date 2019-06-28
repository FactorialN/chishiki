#include <iostream>
#include <interface/analyse.h>


// the main process of the renderer
int main(int argc, char *argv[]){
    fprintf(stderr, "-------------------Chishiki by FactorialN-------------------\n");

    // make sure there is an input direction script
    if (argc < 1 || argc > 2){
        fprintf(stderr, "Please input the name of the script!\n");
        return 0;
    }

    // construct an Analyse Object that controls the whole rendering process
    Analyse *a = new Analyse(argv[1]);
    a->run();
    fprintf(stderr, "---------------------------Done-----------------------------\n");
    return 0;
}