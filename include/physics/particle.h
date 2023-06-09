//
// Created by beloin on 12/03/23.
//

#ifndef INC_2D_PHYSICS_PARTICLE_H
#define INC_2D_PHYSICS_PARTICLE_H

#define GRAVITY 9.8f

#include "vector2.h"
#include "physicsContext.h"

typedef struct {
    Vector2 position;
    Vector2 velocity;
    float mass;
    PhysicsContext context; // TODO: How many padding bytes we have?
} Particle;

Vector2 ComputeGravityForce(Particle *particle);

void CalculateNewPositionAndVelocity(Particle *particle, Vector2 *acceleration);

void CalculateNewPosition(Particle *particle);

Vector2 GetAccelerationToTarget(Particle *particle, Vector2 *target);

#endif //INC_2D_PHYSICS_PARTICLE_H
