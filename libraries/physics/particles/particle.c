#include "vector2.h"
#include "particle.h"

#define TIME_TO_TARGET 200

#include "math.h"

Vector2 ComputeGravityForce(Particle *particle) {
    return (Vector2) {0, -particle->mass * GRAVITY};
}

void CalculateNewPositionAndVelocity(Particle *particle, Vector2 *acceleration) {
    Vector2 *velocity = &particle->velocity;
    float dt = (float) (particle->context.t - particle->context.reset);

    velocity->x = velocity->x + acceleration->x * dt;
    velocity->y = velocity->y + acceleration->y * dt;

    Vector2 *position = &particle->position;
    position->x = position->x + velocity->x * dt;
    position->y = position->y + velocity->y * dt;
}

void CalculateNewPosition(Particle *particle) {
    float dt = (float) (particle->context.t - particle->context.reset);

    Vector2 *velocity = &particle->velocity;
    Vector2 *position = &particle->position;
    position->x = position->x + velocity->x * dt;
    position->y = position->y + velocity->y * dt;
}

Vector2 GetAccelerationToTarget(Particle *particle, Vector2 *target) {
    // S = S0 + (V0 + a*t/2)*t
    Vector2 particlePosition = particle->position;
    Vector2 velocity = particle->velocity;

    float time = TIME_TO_TARGET;

    float xTargetDistance = target->x - particlePosition.x;
    float numeratorX = xTargetDistance - velocity.x * time;
    float accX = numeratorX / (time * time);

    float yTargetDistance = target->y - particlePosition.y;
    float numeratorY = yTargetDistance - velocity.y * time;
    float accY = numeratorY / (time * time);

    // TODO: Find a better way to implement it
    // TODO: Put this inside Simulation.
    if (fabsf(accX) < 0.0000000001 && fabsf(accY) < 0.00000000001) {
        particle->context.reset = particle->context.t;
    }

    return (Vector2) {accX * 2, accY * 2};
};
