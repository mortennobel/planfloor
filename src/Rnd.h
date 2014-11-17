//
// Created by morten on 15/11/14.
//


#pragma once
#include <random>

class Rnd {
    std::random_device rd;
    std::default_random_engine e1;
public:
    Rnd();

    float nextFloat(float min, float maxExcluding);

    int nextInt(int min, int max);

    float next();
};



