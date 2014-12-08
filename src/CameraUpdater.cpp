//
// Created by morten on 08/12/14.
//

#include "CameraUpdater.h"

CameraUpdater::CameraUpdater(kick::GameObject *gameObject,kick::CameraOrthographic *cam)
    : Component(gameObject), cam{cam} {

}

void CameraUpdater::update() {
    glm::ivec2 dim = kick::Engine::context()->getContextSurfaceDim();
    float targetHeight = 600;
    float aspect = dim.x/(float)dim.y;

    cam->setLeft(-(targetHeight * aspect)/2);
    cam->setRight((targetHeight * aspect)/2);
    cam->setBottom(-targetHeight/2);
    cam->setTop(targetHeight/2);
}