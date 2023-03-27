//
// Created by beloin on 16/03/23.
//
#include "vector2.h"

void Negate(Vector2 *const a) {
    a->y = -a->y;
    a->x = -a->x;
}

Vector2 CreateVector(float x, float y) {
    return (Vector2) {x, y};
}
