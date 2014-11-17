//
//  main.cpp
//  PoetryEd
//
//  Created by Morten Nobel-Jørgensen on 29/10/14.
//  Copyright (c) 2014 Morten Nobel-Jørgensen. All rights reserved.
//

#include <iostream>

#include "kick/kick.h"
#import "BuildingFactory.h"
#import "ColorScheme.h"

using namespace kick;

int main(int argc, char * argv[])
{
    Engine::init(argc, argv);
    auto scene = Engine::activeScene();
    auto camera = scene->createOrthographicCamera();
    camera->setClearColor(ColorScheme::backgroundColor);

    scene->createDirectionalLight();

    kick::MeshData meshData;
    std::vector<glm::vec3> positions;
    std::vector<unsigned short> indices;
    BuildingFactory::CreateBuilding().createGeometry(positions,indices);
    meshData.setPosition(positions);
    meshData.setSubmesh(0,indices, MeshType::Triangles);
    meshData.recomputeBounds();
    meshData.recomputeNormals();

        auto gameObject = scene->createGameObject("Building");
    gameObject->transform()->setLocalScale({0.2f,0.2f,0.2f});
        MeshRenderer *meshRenderer = gameObject->addComponent<MeshRenderer>();
        Mesh* mesh = new Mesh();
        mesh->setMeshData(&meshData);
        meshRenderer->setMesh(mesh);

        auto shader = Project::loadShader("assets/shaders/unlit.shader");
        Material* mat = new Material();
    mat->setUniform("mainColor", ColorScheme::wallColor);
        mat->setShader(shader);
        meshRenderer->setMaterial(mat);


    Engine::startMainLoop();

    return 0;
}
