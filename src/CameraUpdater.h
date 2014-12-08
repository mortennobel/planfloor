//
// Created by morten on 08/12/14.
//


#pragma once

#include "kick/kick.h"

class CameraUpdater : public kick::Component, public kick::Updatable {
public:
    kick::CameraOrthographic *cam;
    CameraUpdater (kick::GameObject *gameObject,kick::CameraOrthographic *cam);

    virtual void update();
};



