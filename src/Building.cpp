//
// Created by morten on 13/11/14.
//

#include "Building.h"

void Building::createGeometry(std::vector<glm::vec3>& positions, std::vector<unsigned short>& indices) {
    for (auto& r:rooms){
        r.createGeometry(positions, indices);
    }
}
