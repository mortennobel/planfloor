//
// Created by morten on 09/02/15.
//

#include "Export.h"
#include <iostream>
#include "simple_svg_1.0.0.hpp"

using namespace kick;
using namespace std;

void Export::update() {
    if (MouseInput::pressed(0)){
        auto meshData = mesh->meshData();
        meshData->recomputeBounds();
        auto bounds = meshData->bounds();
        auto offset = -bounds.min;

        // triangles



        using namespace svg;

// Demo page shows sample usage of the Simple SVG library.

        static int imageCount = 0;
            Dimensions dimensions(bounds.diagonal().x, bounds.diagonal().y);
        string s = "planfloor_";
        s = s+std::to_string(imageCount++)+".svg";
            Document doc(s.c_str(), Layout(dimensions, Layout::BottomLeft));

            auto & vertices = meshData->position();
            auto & indices = meshData->submeshIndices(0);

            for (int i=0;i<indices.size();i+=3){
                auto v1 = offset+vertices[indices[i]];
                auto v2 = offset+vertices[indices[i+1]];
                auto v3 = offset+vertices[indices[i+2]];
                doc << (Polygon(Color(0, 0, 0)) << Point(v1.x, v1.y)
                        << Point(v2.x, v2.y) << Point(v3.x, v3.y));

            }

            doc.save();

    }
}
