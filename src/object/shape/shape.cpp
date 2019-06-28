#include <object/shape/shape.h>

/*
* add and get emit
*/
void Shape::addEmit(const Color &em){ 
    emitter = em; 
    isemit = true;
    bsdf = nullptr;
    bssrdf = nullptr;
}

Color Shape::getEmit(){
    return emitter;
}

bool Shape::isEmit(){
    return isemit;
}


/*
* add and get BSDF
*/
void Shape::addBSDF(BSDF *b){ 
    bsdf = b; 
}

BSDF* Shape::getBSDF(){
    return bsdf;
}


/*
* add and get BSSRDF
*/
void Shape::addBSSRDF(BSSRDF *b){ 
    bssrdf = b; 
}

BSSRDF* Shape::getBSSRDF(){
    return bssrdf;
}