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

#define perp(u,v)  ((u).x * (v).y - (u).y * (v).x)  // perp product  (2D)
#define SMALL_NUM   0.00000001 // anything that avoids division overflow

int Wall::intersect(Wall *wall, glm::vec2& I0, glm::vec2 & I1) {
    // from http://geomalgorithms.com/a05-_intersect-1.html
    vec2    u = end - start;
    vec2    v = wall->end - wall->start;
    vec2    w = start - wall->start;
    float     D = perp(u,v);

    // test if  they are parallel (includes either being a point)

    if (fabs(D) < SMALL_NUM) {           // S1 and S2 are parallel
        if (perp(u,w) != 0 || perp(v,w) != 0)  {
            return 0;                    // they are NOT collinear
        }
        // they are collinear or degenerate
        // check if they are degenerate  points
        float du = dot(u,u);
        float dv = dot(v,v);
        if (du==0 && dv==0) {            // both segments are points
            if (start !=  wall->start)         // they are distinct  points
                return 0;
            I0 = start;                 // they are the same point
            return 1;
        }
        if (du==0) {                     // S1 is a single point
            if  (wall->inSegment(start) == 0)  // but is not in S2
                return 0;
            I0 = start;
            return 1;
        }
        if (dv==0) {                     // S2 a single point
            if  (inSegment(wall->start) == 0)  // but is not in S1
                return 0;
            I0 = wall->start;
            return 1;
        }
        // they are collinear segments - get  overlap (or not)
        float t0, t1;                    // endpoints of S1 in eqn for S2
        vec2 w2 = end - wall->start;
        if (v.x != 0) {
            t0 = w.x / v.x;
            t1 = w2.x / v.x;
        }
        else {
            t0 = w.y / v.y;
            t1 = w2.y / v.y;
        }
        if (t0 > t1) {                   // must have t0 smaller than t1
            float t=t0; t0=t1; t1=t;    // swap if not
        }
        if (t0 > 1 || t1 < 0) {
            return 0;      // NO overlap
        }
        t0 = t0<0? 0 : t0;               // clip to min 0
        t1 = t1>1? 1 : t1;               // clip to max 1
        if (t0 == t1) {                  // intersect is a point
            I0 = wall->start +  t0 * v;
            return 1;
        }

        // they overlap in a valid subsegment
        I0 = wall->start + t0 * v;
        I1 = wall->start + t1 * v;
        return 2;
    }

    // the segments are skew and may intersect in a point
    // get the intersect parameter for S1
    float     sI = perp(v,w) / D;
    if (sI < 0 || sI > 1)                // no intersect with S1
        return 0;

    // get the intersect parameter for S2
    float     tI = perp(u,w) / D;
    if (tI < 0 || tI > 1)                // no intersect with S2
        return 0;

    I0 = start + sI * u;                // compute S1 intersect point
    return true;
}

bool Wall::inSegment( glm::vec2 P) {
    if (start.x != end.x) {    // S is not  vertical
        if (start.x <= P.x && P.x <= end.x)
            return true;
        if (start.x >= P.x && P.x >= end.x)
            return true;
    }
    else {    // S is vertical, so test y  coordinate
        if (start.y <= P.y && P.y <= end.y)
            return true;
        if (start.y >= P.y && P.y >= end.y)
            return true;
    }
    return false;
}

bool Wall::isParallel(Wall *w) {
    vec2 thisNormal = end-start;
    vec2 otherNormal = w->end - w->start;

    return fabs(dot(thisNormal, vec2(-otherNormal.y, otherNormal.x))) < SMALL_NUM ;
}

float Wall::length() {
    return glm::length(end - start);
}
