//
// Created by morten on 15/11/14.
//


#pragma once

#include "glm/glm.hpp"

class ColorScheme {
public:
    static glm::vec4 backgroundColor;
    static glm::vec4 wallColor;
    static glm::vec4 floorColor;
    static glm::vec4 furnitureColor;
    static glm::vec4 otherColor;
private:
    static glm::vec4 rgb(int r, int g, int b);
};



