//
// Created by beloin on 29/03/23.
//

#ifndef SWARM_ENGINE_SIMULATION_H
#define SWARM_ENGINE_SIMULATION_H

#include "particle.h"
#include "ant/ant.h"

#define DEFAULT_CENTER_DIST 50.0f
#define S_LENGTH 1

void InitializeSimulation(int pmin, int pmax);

Ant *GetSimulationArray();

int GetSimulationLength();

#endif //SWARM_ENGINE_SIMULATION_H
