//
// Created by morten on 13/11/14.
//


#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "kick/kick.h"

class Wall {
    glm::vec2 start;
    glm::vec2 end;
    float thickness = 10;
public:
    Wall(glm::vec2 const &start, glm::vec2 const &end)
            : start(start), end(end) {
    }

    void createGeometry(std::vector<glm::vec3>& positions, std::vector<unsigned short>& indices);
};



