//
// Created by beloin on 27/03/23.
//

#ifndef SWARM_ENGINE_GL_PARTICLE_ADAPTER_H
#define SWARM_ENGINE_GL_PARTICLE_ADAPTER_H

#include "../../include/physics/vector2.h"

#define DEFAULT_CENTER_DIST 50.0f

// For now everyone will be an equilateral triangle.
typedef struct {
    Vector2 *center;

    float centerDistance; // if: r = 2/3 * h. So h = 3/2*r

    // Upper Point:
    // X = X
    // Y = Y + 2/3 * h
    Vector2 upper;
    // Left point:
    // X = X - sqrt(3) * h / 3
    // Y = Y - 1/3 *h
    Vector2 left;
    // Right point:
    // X = X + sqrt(3) * h / 3
    // Y = Y - 1/3 *h
    Vector2 right;
} TriangleVector2;

TriangleVector2 CreateTriangle(Vector2 *particle, int height, int width);

void GenerateFloatArray(TriangleVector2 *, float output[9]);

#endif //SWARM_ENGINE_GL_PARTICLE_ADAPTER_H
