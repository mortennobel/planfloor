//
// Created by morten on 25/11/14.
//


#pragma once

#include "kick/kick.h"

class BuildingComponent : public kick::Component, public kick::Updatable {
    std::shared_ptr<kick::Mesh> mesh;
public:
    BuildingComponent(kick::GameObject *gameObject, std::shared_ptr<kick::Mesh> mesh) : Component(gameObject), mesh{mesh} {
        updateMesh();
    }
    virtual void update();
private:
    void updateMesh();
};



