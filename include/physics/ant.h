//
// Created by beloin on 02/04/23.
//

#ifndef SWARM_ENGINE_ANT_H
#define SWARM_ENGINE_ANT_H

#include "particle.h"
#include "aabb.h"

#define START_ATTRACTION 10
#define ATTRACTION_THRESHOLD 10

typedef struct {
    Particle bodyCenter;
    AABB aabb; // TODO: Could use a circle instead of AABB, since is radius and the formula is simple.
    float attraction;
} Ant;

// TODO: Here we will implement the real part where we will be using attraction

void TestAttraction(Ant *ants, int size);
Ant CreateAnt();



#endif //SWARM_ENGINE_ANT_H
