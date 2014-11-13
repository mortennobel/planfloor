//
// Created by morten on 13/11/14.
//


#pragma once

#include "Room.h"

class Building {
public:
    std::vector<Room> rooms;

    //std::vector<Room> furnitures;

    void createGeometry(std::vector<glm::vec3>& positions, std::vector<unsigned short>& indices);
};



