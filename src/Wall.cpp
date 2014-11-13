//
// Created by morten on 13/11/14.
//

#include "Wall.h"

using namespace glm;

void Wall::createGeometry(std::vector<glm::vec3>& positions, std::vector<unsigned short>& indices) {
    vec2 normal = (0.5f*thickness)*normalize(end - start);
    vec2 ortho{normal.y,-normal.x};

    positions.push_back(vec3(start-ortho,0.0));
    positions.push_back(vec3(start+ortho,0.0));
    positions.push_back(vec3(end+ortho,0.0));

    positions.push_back(vec3(end+ortho,0.0));
    positions.push_back(vec3(end-ortho,0.0));
    positions.push_back(vec3(start-ortho,0.0));

    indices.push_back(indices.size());
    indices.push_back(indices.size());
    indices.push_back(indices.size());

    indices.push_back(indices.size());
    indices.push_back(indices.size());
    indices.push_back(indices.size());

}
