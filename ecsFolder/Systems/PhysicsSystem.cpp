#include "PhysicsSystem.h"
#include "../World/World.h"

void PhysicsSystem::update(World& world, float movementMul) {
    for (auto entity : entities) {
        if (world.velocities.find(entity) == world.velocities.end() ||
            world.gravities.find(entity) == world.gravities.end() ||
            world.jumps.find(entity) == world.jumps.end()) {
            continue;
        }

        auto& velocity = world.velocities[entity];
        auto& gravity = world.gravities[entity];
        auto& jump = world.jumps[entity];

        if (!jump.isGrounded) {
            velocity.dy -= gravity.force * movementMul;
        }
    }
}

void PhysicsSystem::AddEntity(Entity entity, World& world) {
    if (world.velocities.contains(entity) &&
        world.gravities.contains(entity) &&
        world.jumps.contains(entity)) {
        entities.insert(entity);
    }
}