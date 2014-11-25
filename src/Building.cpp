//

#include "Building.h"
#include "glm/glm.hpp"
#import "Parameters.h"
#include <iostream>
#include <map>
#include <set>
#include <glm/gtx/vector_angle.hpp>

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
glm::vec3 Building::findSplitPoint(const Halfedge* edge){
    vec3 direction =(edge->vert->position - edge->prev->vert->position);
    float length = glm::length(direction);
    assert (length >= 2*Parameters::minimumWallLength);
    float offset = Parameters::minimumWallLength+rnd->nextInt(0, (int)(floor( (length- 2*Parameters::minimumWallLength)/10)))*10;
    vec3 offsetPos = (direction * (offset / length));
    return edge->prev->vert->position + offsetPos;
}

kick::Ray Building::edgeToRay(const Halfedge* edge, float rotateZ){
    vec3 direction = edge->vert->position - edge->prev->vert->position;

    direction = glm::rotateZ(direction, rotateZ);

    return kick::Ray {edge->prev->vert->position, direction};
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

    float rotation;
    if (rnd->next() < Parameters::splitRotateChange){
        rotation = rnd->next()>0.5f?M_PI_4:3*M_PI_4;
    } else {
        rotation = M_PI_2;
    }
    kick::Ray edgeDirection = edgeToRay(edge, rotation);
    edgeDirection.setOrigin(findSplitPoint(edge));


    Halfedge* otherEdge = nullptr;
    vec3 otherPoint;
    for (auto e:face->circulate()){
        if (e == edge){
            continue;
        }
        kick::Ray otherEdgeDirection = edgeToRay(e,0);
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
        if (length(otherPoint - otherEdge->vert->position) < Parameters::minimumWallLength ||
                length(otherPoint - otherEdge->prev->vert->position) < Parameters::minimumWallLength){
            return;
        }

        Vertex* v1 = edge->split();
        v1->position = edgeDirection.origin();
        Vertex* v2 = otherEdge->split();
        v2->position = otherPoint;
        Halfedge* newHalfedge = edge->face->connect(v1,v2);

        if (face->area() < Parameters::minimumRoomArea ||  newHalfedge->face->area() < Parameters::minimumRoomArea ){
            newHalfedge->dissolve();
            v1->dissolve();
            v2->dissolve();
        }
    }
}

Halfedge * Building::findRandomEdge() {
    int randomRoom = rnd->nextInt(0, hmesh.faceCount()-1);
    Face *face = hmesh.face(randomRoom);
    Halfedge *edge = face->halfedge;
    int randomWall = rnd->nextInt(1, face->edgeCount()-1);
    for (int i=0;i<randomWall;i++){
        edge = edge->next;
    }
    return edge;
}

void Building::cut() {


    Halfedge * edge = findRandomEdge();

    if (edge->face->edgeCount() != 4){
        return;
    }

    if (edge->face->area() / 4 < Parameters::minimumRoomArea){
        return;
    }

    vec3 centerPos{0};
    for (auto he: edge->face->circulate()){
        centerPos += he->vert->position * 0.25f;
    }


    Halfedge * edgeNext = edge->next;

    Vertex *edgeVertex = edge->split();
    Vertex *edgeNextVertex = edgeNext->split();

    Vertex *centerVertex = edge->face->split(edge->vert);
    centerVertex->position = centerPos;

    /*// find opposite directed
    while (abs(angle(normalize(edge->direction()),normalize(edgeNext->direction()))) < 0.1f  ){
        edgeNext = edge->next;
    }

    kick::Ray ray = edgeToRay(edge, M_PI/2);
    kick::Ray rayNext = edgeToRay(edgeNext, M_PI/2);

    vec3 outPoint1, outPoint2;

    if (!ray.closestPoints(rayNext, outPoint1, outPoint2)){
        return;
    }
    if (outPoint1 !=  outPoint2) {
        return;
    }
    */
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
