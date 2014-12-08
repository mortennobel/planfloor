//
// Created by morten on 25/11/14.
//

#include "BuildingComponent.h"
#include "BuildingFactory.h"
#include <iostream>

using namespace kick;
using namespace std;

void BuildingComponent::update() {
    if (MouseInput::down(0)){
        updateMesh();
    }
}

void BuildingComponent::updateMesh() {
    auto meshData = make_shared<MeshData>();
    std::vector<glm::vec3> positions;
    std::vector<unsigned short> indices;
    BuildingFactory::CreateBuilding().createGeometry(positions,indices);
    meshData->setPosition(positions);
    meshData->setSubmesh(0,indices, MeshType::Triangles);
    meshData->recomputeBounds();
    meshData->recomputeNormals();
    mesh->setMeshData(meshData);
}
