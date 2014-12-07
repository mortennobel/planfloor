//
// Created by morten on 13/11/14.
//

#include "BuildingFactory.h"

using namespace glm;

kick::Random BuildingFactory::rnd;

Building BuildingFactory::CreateBuilding() {
    Building building{&rnd};
    building.build();
    return building;
}
