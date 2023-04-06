//
// Created by beloin on 29/03/23.
//

#include "simulation.h"
#include "stdlib.h"

char isInitialized = 0;
Ant ants[S_LENGTH];

int GetSimulationLength() {
    return S_LENGTH;
}

Ant *GetSimulationArray() {
    return &ants[0];
}

void InitializeSimulation(int pmin, int pmax) {
    if (isInitialized) return;

    isInitialized = 1;

    float aspect = 0.3f;
    for (int i = 0; i < S_LENGTH; ++i) {
        unsigned int rx = (unsigned int) random();
        unsigned int ry = (unsigned int) random();
        rx = rx % pmax;
        ry = ry % pmax;

        if (rx < pmin) rx = pmin;
        if (ry < pmin) ry = pmin;


        float x = 100.f + (float) rx * aspect;
        float y = 400 + (float) ry * aspect;

        Particle pTemp = (Particle) {(Vector2) {(float) x, (float) y}, (Vector2) {2, 0}, 1, {0, 0}};
        ants[i] = (Ant) {pTemp, START_ATTRACTION};
    }

}




