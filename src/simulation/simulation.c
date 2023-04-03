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

#if 0

void Initialize(int pmin, int pmax) {
    if (isInitialized) return;

    isInitialized = 1;
    for (int i = 0; i < S_LENGTH; ++i) {
        unsigned int x = (unsigned int) random();
        unsigned int y = (unsigned int) random();
        x = x % pmax;
        y = y % pmax;

        if (x < pmin) x = pmin;
        if (y < pmin) y = pmin;

        Particle pTemp = (Particle) {(Vector2) {(float) x, (float) y}, (Vector2) {0, 0}, 1};

        Vector2 min = (Vector2) {pTemp.position.x - DEFAULT_CENTER_DIST, pTemp.position.y - DEFAULT_CENTER_DIST};
        Vector2 max = (Vector2) {pTemp.position.x + DEFAULT_CENTER_DIST, pTemp.position.y + DEFAULT_CENTER_DIST};
        AABB aabb = (AABB) {min, max};
        ants[i] = (Ant) {pTemp, aabb, ATTRACTION_THRESHOLD};
    }

}

#else

void InitializeSimulation(int pmin, int pmax) {
    if (isInitialized) return;

    isInitialized = 1;

    float aspect = 0.3f;
    for (int i = 0; i < 20; ++i) {
        unsigned int rx = (unsigned int) random();
        unsigned int ry = (unsigned int) random();
        rx = rx % pmax;
        ry = ry % pmax;

        if (rx < pmin) rx = pmin;
        if (ry < pmin) ry = pmin;


        float x = 100.f + (float) rx * aspect;
        float y = 100.f + (float) ry * aspect;


        Particle pTemp = (Particle) {(Vector2) {(float) x, (float) y}, (Vector2) {0, 0}, 1};

        Vector2 min = (Vector2) {pTemp.position.x - DEFAULT_CENTER_DIST, pTemp.position.y - DEFAULT_CENTER_DIST};
        Vector2 max = (Vector2) {pTemp.position.x + DEFAULT_CENTER_DIST, pTemp.position.y + DEFAULT_CENTER_DIST};
        AABB aabb = (AABB) {min, max};
        ants[i] = (Ant) {pTemp, aabb, ATTRACTION_THRESHOLD};
    }

}

#endif



