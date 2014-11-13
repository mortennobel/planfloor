//
// Created by morten on 13/11/14.
//


#pragma once

#include <vector>
#include "Wall.h"
#include "kick/kick.h"

class Room {
public:
    std::vector<Wall> walls;

    void createGeometry(std::vector<glm::vec3>& positions, std::vector<unsigned short>& indices);
};



