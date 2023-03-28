//
// Created by beloin on 27/03/23.
//

#ifndef SWARM_ENGINE_PHYSICSCONTEXT_H
#define SWARM_ENGINE_PHYSICSCONTEXT_H

typedef enum {
    S, MS_100, MS_500
} Resolution;

typedef struct {
    long double dt; // Simulation Time in seconds
    Resolution resolution;
} PhysicsContext;

#endif //SWARM_ENGINE_PHYSICSCONTEXT_H
