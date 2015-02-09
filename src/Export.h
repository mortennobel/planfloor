//
// Created by morten on 08/12/14.
//


#pragma once

#include "kick/kick.h"

class Export : public kick::Component, public kick::Updatable {
    std::shared_ptr<kick::Mesh> mesh;
public:
    Export(kick::GameObject *gameObject, std::shared_ptr<kick::Mesh> mesh) : Component(gameObject), mesh(mesh) {
    }


    virtual void update();
};