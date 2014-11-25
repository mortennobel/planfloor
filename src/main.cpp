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
#import "BuildingComponent.h"

using namespace kick;

int main(int argc, char * argv[])
{
    Engine::init(argc, argv);
    auto scene = Engine::activeScene();
    auto camera = scene->createOrthographicCamera();
    camera->setClearColor(ColorScheme::backgroundColor);

    scene->createDirectionalLight();

    auto gameObject = scene->createGameObject("Building");
    gameObject->transform()->setLocalScale({0.2f,0.2f,0.2f});
    MeshRenderer *meshRenderer = gameObject->addComponent<MeshRenderer>();
    Mesh* mesh = new Mesh();
    gameObject->addComponent<BuildingComponent>(mesh);
    meshRenderer->setMesh(mesh);

    auto shader = Project::loadShader("assets/shaders/unlit.shader");
    Material* mat = new Material();
    mat->setUniform("mainColor", ColorScheme::wallColor);
    mat->setShader(shader);
    meshRenderer->setMaterial(mat);

    auto cube = scene->createCube();
    cube->transform()->setLocalScale({100.0f/2,100.0f/2,1.0f});
    cube->transform()->setLocalPosition({300,-250,0});

    cube->setMaterial(mat);

    Engine::startMainLoop();

    return 0;
}
