//
// Created by morten on 15/11/14.
//

#include "ColorScheme.h"

glm::vec4 ColorScheme::rgb(int r, int g, int b) {
    return glm::vec4{r/255.0f, g/255.0f, b/255.0f, 1.0f};
}


glm::vec4 ColorScheme::backgroundColor = rgb(17,38,59);
glm::vec4 ColorScheme::wallColor = rgb(106,146,182);
glm::vec4 ColorScheme::floorColor = rgb(216,231,234);
glm::vec4 ColorScheme::furnitureColor = rgb(178,176,125);
glm::vec4 ColorScheme::otherColor = rgb(228,202,81);

