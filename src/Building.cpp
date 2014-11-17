//

#include "Building.h"
#include "glm/glm.hpp"
#import "Parameters.h"
#include <iostream>
#include <map>
#include <set>

using namespace glm;
using namespace std;

//
// Created by morten on 13/11/14.
Building::Building(Rnd *rnd) : rnd(rnd) {
}

void Building::createGeometry(std::vector<glm::vec3>& positions, std::vector<unsigned short>& indices) {
    for (auto& r:rooms){
        r.createGeometry(positions, indices);
    }
}

void Building::build() {
    hmesh.clear();

    buidOuterwalls();

    int numberOfSubdivides = rnd->nextInt(0, 50);
    for (int i = numberOfSubdivides; i > 0; i--){
        subdivide();
    }

    convertHMeshToRooms();
}

void Building::convertHMeshToRooms(){
    map<Face*, int> faceMap;
    for (auto facePtr : hmesh.faces()){
        rooms.emplace_back();
        faceMap.insert({facePtr, rooms.size()-1});
    }
    for (Halfedge* edgesPtr : hmesh.halfedgesSingleSide()){
        bool boundary = edgesPtr->isBoundary();
        vec3 toPosition = edgesPtr->vert->position;
        vec3 fromPosition = edgesPtr->prev->vert->position;
        Room& room = rooms[faceMap[edgesPtr->face]];
        room.walls.push_back(new Wall((vec2)fromPosition, (vec2)toPosition, boundary));
    }
}

void Building::subdivide() {
    if (rnd->next()>Parameters::splitRoomChange){
        split();
    } else {
        cut();
    }
}

kick::Ray edgeToRay(Halfedge* edge, bool ortho){
    vec3 direction = (edge->vert->position - edge->prev->vert->position);
    if (ortho){
        direction = cross(vec3{0,0,1}, direction);
    }
    return kick::Ray {(edge->prev->vert->position + edge->vert->position)*0.5f, direction};
}

void Building::split() {
    int randomRoom = rnd->nextInt(0, hmesh.faceCount()-1);
    Face* face = hmesh.face(randomRoom);
    int randomWall = rnd->nextInt(1, face->edgeCount()-1);
    Halfedge* edge = face->halfedge;
    for (int i=0;i<randomWall;i++){
        edge = edge->next;
    }
    if (edge->length() <= 2*Parameters::minimumWallLength){
        return;
    }

    kick::Ray edgeDirection = edgeToRay(edge, true);



    Halfedge* otherEdge = nullptr;
    vec3 otherPoint;
    for (auto e:face->circulate()){
        if (e == edge){
            continue;
        }
        kick::Ray otherEdgeDirection = edgeToRay(e,false);
        vec3 point1, point2;
        if (edgeDirection.closestPoints(otherEdgeDirection, point1, point2)){
            if (length2(point1 - point2) < 0.1){
                float otherEdgeLength = e->length();
                if (length(e->vert->position - point2) <= otherEdgeLength &&
                        length(e->prev->vert->position - point2) <= otherEdgeLength){

                    otherEdge = e;
                    otherPoint =  point2;
                }
            }
        }
    }



    if (otherEdge){
        Vertex* v1 = edge->split();
        v1->position = edgeDirection.origin();
        Vertex* v2 = otherEdge->split();
        v2->position = otherPoint;
        edge->face->connect(v1,v2);
    }
}

void Building::cut() {

}

void Building::doorsAndWindows() {

}



void Building::buidOuterwalls() {
    rooms.emplace_back();
    Room* room = &rooms.back();
    float width = rnd->nextInt(50, 250)*10;
    float height = rnd->nextInt(50, 250)*10;
    float widthH = width/2;
    float heightH = height/2;

    vector<glm::vec3> vertices;
    vector<std::vector<int> >  indices;
    vertices.push_back(glm::vec3{-widthH,-heightH,0.0f});
    vertices.push_back(glm::vec3{-widthH,heightH,0.0f});
    vertices.push_back(glm::vec3{widthH,heightH,0.0f});
    vertices.push_back(glm::vec3{widthH,-heightH,0.0f});
    indices.emplace_back();
    indices.back().push_back(0);
    indices.back().push_back(1);
    indices.back().push_back(2);
    indices.back().push_back(3);
    hmesh.build(vertices, indices);
}
