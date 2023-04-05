//
// Created by beloin on 02/04/23.
//

#include "../../include/physics/ant.h"
#include "stdlib.h"

bool checkAABB(Ant *a, Ant *b);

void TestAttraction(Ant *ants, int size) {

    // n + (n-1) + (n-2) + (n-3) ... -> O(N²), porém,
    for (int i = 0; i < size; ++i) {

        Ant currentAnt = ants[i];

        int attractedAntsLength = 0;
        double attraction = 0;
        Ant **attractedAnts = (Ant **) malloc(sizeof(Ant *) * size);

        for (int j = i; j < size; ++j) {
            Ant *compareAnt = &ants[j];
            // TODO: This gets in a radius independent of the position
            if (checkAABB(&currentAnt, compareAnt)) {
                attractedAnts[attractedAntsLength] = compareAnt;
                // OR:?
                attractedAnts[attractedAntsLength] = (Ant *) malloc(sizeof(Ant *));
                *attractedAnts[attractedAntsLength] = ants[j];

                attractedAntsLength++;

                attraction += compareAnt->attraction;
            }
        }

        if (attraction >= ATTRACTION_THRESHOLD) {
            // Calculate the centroid of all the points of the `attractedAnts`
            // Set the ant position to there
//            GetAccelerationToTarget();
        }
    }
}

bool checkAABB(Ant *a, Ant *b) {
    return AABBvsAABB(&a->aabb, &b->aabb);
}