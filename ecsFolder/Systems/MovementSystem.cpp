#include "MovementSystem.h"
#include "../World/World.h"

void MovementSystem::update(World& world, float movementMul) {
    for (auto entity : entities) {
        if (!world.velocities.contains(entity) ||
            !world.positions.contains(entity) ||
            !world.movementInputs.contains(entity) ||
            !world.jumps.contains(entity) ||
            !world.gravities.contains(entity)) {
            continue;
        }

        auto& velocity = world.velocities[entity];
        auto& position = world.positions[entity];
        auto& input = world.movementInputs[entity];
        auto& jump = world.jumps[entity];
        auto& gravity = world.gravities[entity];

        if (input.right) {
            velocity.dx += velocity.acceleration * movementMul;
        } else if (input.left) {
            velocity.dx -= velocity.acceleration * movementMul;
        } else {
            if (velocity.dx > 0) {
                velocity.dx = std::max(0.f, velocity.dx - velocity.deceleration * movementMul);
            } else if (velocity.dx < 0) {
                velocity.dx = std::min(0.f, velocity.dx + velocity.deceleration * movementMul);
            }
        }

        velocity.dx = std::clamp(velocity.dx, -velocity.maxSpeed, velocity.maxSpeed);

        if (input.jump && !input.wasJumping && jump.isGrounded) {
            velocity.dy = jump.impulse;
            jump.isGrounded = false;
        }

        input.wasJumping = input.jump;

        position.x += velocity.dx * movementMul;
        position.y += velocity.dy * movementMul;
    }
}

void MovementSystem::AddEntity(Entity entity, World& world) {
    if (world.positions.contains(entity) &&
        world.velocities.contains(entity) &&
        world.movementInputs.contains(entity) &&
        world.colliders.contains(entity)) {
        entities.insert(entity);
    }
}
