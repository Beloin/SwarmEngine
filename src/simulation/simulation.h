//
// Created by beloin on 29/03/23.
//

#ifndef SWARM_ENGINE_SIMULATION_H
#define SWARM_ENGINE_SIMULATION_H

#include "../../include/physics/particle.h"

#define P_SIZE 20

void Initialize(int pmin, int pmax);
Particle* GetParticleArray();
int GetParticlesLength();

#endif //SWARM_ENGINE_SIMULATION_H
