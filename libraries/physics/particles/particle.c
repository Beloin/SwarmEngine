#include <stdlib.h>
#include "vector2.h"
#include "particle.h"

#define TIME_TO_TARGET 200
#define DEFAULT_ACC .5f

#include "math.h"

Vector2 ComputeGravityForce(Particle *particle) {
    return (Vector2) {0, -particle->mass * GRAVITY};
}

void CalculateNewPositionAndVelocity(Particle *particle, Vector2 *acceleration, const PhysicsContext *context) {
    Vector2 *velocity = &particle->velocity;
    float dt = (float) (context->t - context->reset);

    velocity->x = velocity->x + acceleration->x * dt;
    velocity->y = velocity->y + acceleration->y * dt;

    Vector2 *position = &particle->position;
    position->x = position->x + velocity->x * dt;
    position->y = position->y + velocity->y * dt;
}

void CalculateNewPosition(Particle *particle, const PhysicsContext *context) {
    float dt = (float) context->t;

    Vector2 *velocity = &particle->velocity;
    Vector2 *position = &particle->position;
    position->x = position->x + velocity->x * dt;
    position->y = position->y + velocity->y * dt;
}


Vector2 GetAccelerationToTarget(Particle *particle, Vector2 *target, PhysicsContext *physicsContext) {
    // S = S0 + (V0 + a*t/2)*t
    Vector2 particlePosition = particle->position;
    Vector2 velocity = particle->velocity;

    float baseLine = (float) (physicsContext->t - physicsContext->reset);

    float time = TIME_TO_TARGET;
//    float time = TIME_TO_TARGET + baseLine * (1 - exp(-baseLine/10));
//    float time = TIME_TO_TARGET + physicsContext->t * (4 - exp(-physicsContext->t));


    float xTargetDistance = target->x - particlePosition.x;
    float numeratorX = xTargetDistance - velocity.x * time;
    float accX = numeratorX / (time * time);

    float yTargetDistance = target->y - particlePosition.y;
    float numeratorY = yTargetDistance - velocity.y * time;
    float accY = numeratorY / (time * time);

    if (fabsf(xTargetDistance) < 0.01 && fabsf(yTargetDistance) < 0.01) {
        physicsContext->reset = physicsContext->t;
    }

    return (Vector2) {accX * 2, accY * 2};
};
