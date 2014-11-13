//
// Created by morten on 13/11/14.
//

#include "Room.h"

void Room::createGeometry(std::vector<glm::vec3>& positions, std::vector<unsigned short>& indices) {
    for (auto & w : walls){
        w.createGeometry(positions, indices);
    }
}
