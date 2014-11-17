//
// Created by morten on 13/11/14.
//


#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "kick/kick.h"

class Room;

class Wall {
public:
    glm::vec2 start;
    glm::vec2 end;
    float thickness = 10;
    bool outerWall;

    Wall(glm::vec2 const &start, glm::vec2 const &end,bool outerWall)
            : start(start), end(end),outerWall(outerWall) {
        thickness = (outerWall ? 20:10);
    }

    void createGeometry(std::vector<glm::vec3>& positions, std::vector<unsigned short>& indices);

    int intersect(Wall *wall, glm::vec2& intersectionPointStart, glm::vec2 & intersectionPointEnd);

    bool inSegment( glm::vec2 P);

    bool isParallel(Wall* w);

    float length();
};



