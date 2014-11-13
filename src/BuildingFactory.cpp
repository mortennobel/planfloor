//
// Created by morten on 13/11/14.
//

#include "BuildingFactory.h"

using namespace glm;

Building BuildingFactory::CreateBuilding() {
    Building building;
    building.rooms.emplace_back();
    building.rooms.back().walls.emplace_back(vec2{-25,-25},vec2{-25,25});
    building.rooms.back().walls.emplace_back(vec2{-25,25},vec2{25,25});
    building.rooms.back().walls.emplace_back(vec2{25,25},vec2{25,-25});
    building.rooms.back().walls.emplace_back(vec2{25,-25},vec2{-25,-25});
    return building;
}
