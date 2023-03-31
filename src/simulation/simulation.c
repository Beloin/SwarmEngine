//
// Created by beloin on 29/03/23.
//

#include "simulation.h"
#include "stdlib.h"

char isInitialized = 0;
Particle particles[P_SIZE];

int GetParticlesLength() {
    return P_SIZE;
}

Particle *GetParticleArray() {
    return &particles[0];
}

void Initialize(int pmin, int pmax) {
    if (isInitialized) return;

    isInitialized = 1;
    for (int i = 0; i < 20; ++i) {
        unsigned int x = (unsigned int) random();
        unsigned int y = (unsigned int) random();
        x = x % pmax;
        y = y % pmax;

        if (x < pmin) x = pmin;
        if (y < pmin) y = pmin;

        particles[i] = (Particle) {(Vector2) {(float) x, (float) y}, (Vector2) {0, 0}, 1};
    }

}