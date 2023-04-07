//
// Created by beloin on 02/04/23.
//

#include <stdio.h>
#include "ant.h"
#include "stdlib.h"

bool checkAABB(Ant *a, Ant *b);

Vector2 getCentroid(Ant **pArr, int length);

void SimulateAnt(Ant *ant, Ant *ants, int size) {

    int attractedAntsLength = 0;
    double attraction = 0;
    Ant **attractedAnts = (Ant **) malloc(sizeof(Ant *) * size);

    for (int i = 0; i < size; ++i) {
        Ant *compareAnt = &ants[i];
        // TODO: This gets in a radius independent of the position
        if (checkAABB(ant, compareAnt)) {
            attractedAnts[attractedAntsLength] = compareAnt;
            attractedAntsLength++;
            attraction += compareAnt->attraction;
        }
    }

    if (attraction >= ATTRACTION_THRESHOLD) {
        // Calculate the centroid of all the points of the `attractedAnts`
        // Set the ant position to there
        Vector2 centroid = getCentroid(attractedAnts, attractedAntsLength);
        Vector2 acc = GetAccelerationToTarget(&ant->bodyCenter, &centroid);
        CalculateNewPositionAndVelocity(&ant->bodyCenter, &acc);
    }

    // Free the created pointer
    free(attractedAnts);
}

void SimulateAnts(Ant *ants, int size, PhysicsContext *context) {

    // n + (n-1) + (n-2) + (n-3) ...
    for (int i = 0; i < size; ++i) {

        Ant *currentAnt = &ants[i];

        int attractedAntsLength = 0;
        double attraction = 0;
        Ant **attractedAnts = (Ant **) malloc(sizeof(Ant *) * size);

        for (int j = i; j < size; ++j) {
            Ant *compareAnt = &ants[j];
            if (checkAABB(currentAnt, compareAnt)) {
                attractedAnts[attractedAntsLength] = compareAnt;

                attractedAntsLength++;

                attraction += compareAnt->attraction;
            }
        }

        if (attraction >= ATTRACTION_THRESHOLD) {
            // Calculate the centroid of all the points of the `attractedAnts`
            // Set the ant position to there
            Vector2 centroid = getCentroid(attractedAnts, attractedAntsLength);
            Vector2 acc = GetAccelerationToTarget(&currentAnt->bodyCenter, &centroid);
            CalculateNewPositionAndVelocity(&currentAnt->bodyCenter, &acc);
        }

        // Free the created pointer
        free(attractedAnts);
    }
}

Ant CreateAnt(float x, float y) {
    Particle pTemp = (Particle) {CreateVector(x, y), (Vector2) {0, 0}, 1, {0, 0}};

    return (Ant) {pTemp, START_ATTRACTION};
}

// TODO: Could use a circle instead of AABB, since is radius and the formula is simple.
AABB GetAABBFromAnt(Ant *ant, float AABBSize) {
    Particle *pTemp = &ant->bodyCenter;
    Vector2 min = CreateVector(pTemp->position.x - AABBSize, pTemp->position.y - AABBSize);
    Vector2 max = CreateVector(pTemp->position.x + AABBSize, pTemp->position.y + AABBSize);
    AABB aabb = (AABB) {min, max};
    return aabb;
}


bool checkAABB(Ant *a, Ant *b) {
    float size = 150.f;
    AABB aabb1 = GetAABBFromAnt(a, size);
    AABB aabb2 = GetAABBFromAnt(b, size);
    return AABBvsAABB(&aabb1, &aabb2);
}

Vector2 getCentroid(Ant **pArr, int length) {
    // S={(x1,y1),(x2,y2),…(xn,yn)}
    double xCount = 0;
    double yCount = 0;
    for (int i = 0; i < length; ++i) {
        Particle *particle = &pArr[i]->bodyCenter;
        xCount += particle->position.x;
        yCount += particle->position.y;
    }

    return (Vector2) {(float) (xCount / length), (float) (yCount / length)};
}
