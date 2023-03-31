#include "vector2.h"
#include "particle.h"


Vector2 ComputeGravityForce(Particle *particle) {
    return (Vector2) {0, -particle->mass * GRAVITY};
}

void CalculateNewPositionAndVelocity(Particle *particle, Vector2 *acceleration, const PhysicsContext *context) {
    Vector2 *velocity = &particle->velocity;
    float dt = (float) context->dt;

    velocity->x = velocity->x + acceleration->x * dt;
    velocity->y = velocity->y + acceleration->y * dt;

    Vector2 *position = &particle->position;
    position->x = position->x + velocity->x * dt;
    position->y = position->y + velocity->y * dt;
}

void CalculateNewPosition(Particle *particle, const PhysicsContext *context) {
    float dt = (float) context->dt;

    Vector2 *velocity = &particle->velocity;
    Vector2 *position = &particle->position;
    position->x = position->x + velocity->x * dt;
    position->y = position->y + velocity->y * dt;
}
