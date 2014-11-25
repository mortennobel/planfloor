//
// Created by morten on 13/11/14.
//


#pragma once

#include "Room.h"
#import "Rnd.h"
#include "simplehmesh/HMesh.h"

class Building {
    Rnd *rnd;
    HMesh hmesh;
public:

    Building(Rnd *rnd);

    std::vector<Room> rooms;

    //std::vector<Room> furnitures;

    void build();

    void createGeometry(std::vector<glm::vec3>& positions, std::vector<unsigned short>& indices);

private:
    void buidOuterwalls();

    // Either call split or cut
    void subdivide();

    // split the room by a plane
    void split();

    // split the room using two or more line segments
    void cut();

    void doorsAndWindows();

    // return true if the a new wall intersect the any of the existing lines
    bool intersect(Wall* wall);

    kick::Ray edgeToRay(const Halfedge* edge, float rotateZ=0);
    glm::vec3 findSplitPoint(const Halfedge* edge);

    void convertHMeshToRooms();

    Halfedge *findRandomEdge();
};



