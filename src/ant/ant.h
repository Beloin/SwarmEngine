//
// Created by beloin on 02/04/23.
//

#ifndef SWARM_ENGINE_ANT_H
#define SWARM_ENGINE_ANT_H


#include "particle.h"
#include "aabb.h"

#define START_ATTRACTION 10
// This needs to be at least 1.
#define ATTRACTION_THRESHOLD 1

typedef struct {
    Particle bodyCenter;
    float attraction;
} Ant;

void SimulateAnts(Ant *ants, int size, PhysicsContext *context);

void SimulateAnt(Ant *ant, Ant *ants, int size);

Ant CreateAnt(float x, float y);

AABB GetAABBFromAnt(Ant *ant, float AABBSize);

#endif //SWARM_ENGINE_ANT_H
