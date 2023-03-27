//
// Created by beloin on 11/03/23.
//

#ifndef INC_2D_PHYSICS_VECTOR2_H
#define INC_2D_PHYSICS_VECTOR2_H

typedef struct {
    float x;
    float y;
} Vector2;

void Negate(Vector2*);
Vector2 CreateVector(float x, float y);


#endif //INC_2D_PHYSICS_VECTOR2_H
