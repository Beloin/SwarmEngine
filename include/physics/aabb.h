//
// Created by beloin on 25/03/23.
//

#ifndef INC_2D_PHYSICS_AABB_H
#define INC_2D_PHYSICS_AABB_H

#include <stdbool.h>
#include "vector2.h"

typedef struct {
    Vector2 min;
    Vector2 max;
} AABB;

bool AABBvsAABB(AABB *a, AABB *b);

// TODO: implement strategy type for when collision are true
//  Could also use a DBVT

// TODO: Remember, when moving, you have to decompose the vector X and Y, using cos and sin

#endif //INC_2D_PHYSICS_AABB_H
