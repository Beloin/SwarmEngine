//
// Created by beloin on 02/04/23.
//
#include "aabb.h"

bool AABBvsAABB(AABB *a, AABB *b) {
    // If its inside.
    if (a->max.x < b->min.x || a->min.x > b->max.x) {
        return false;
    }

    if (a->max.y < b->min.y || a->min.y < b->max.y) {
        return false;
    }

    return true;
}
