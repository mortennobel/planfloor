//
// Created by morten on 15/11/14.
//

#include "Rnd.h"

Rnd::Rnd() : e1(rd()) {
#ifdef DEBUG
    //e1.seed(2);
#endif
}

float Rnd::nextFloat(float min, float maxExcluding) {
    float r = next();
    while (r == 1.0f){
        r = next();
    }
    return r*(maxExcluding-min) + min;
}

int Rnd::nextInt(int min, int max) {
    return (int)floor(nextFloat(min, max));
}

float Rnd::next(){
    return std::generate_canonical<float, 32>(e1);;
}

