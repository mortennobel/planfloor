//
// Created by morten on 13/11/14.
//


#include "Building.h"

#pragma once


class BuildingFactory {
    static kick::Random rnd;
public:
    static Building CreateBuilding();
};



