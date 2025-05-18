#include "CollisionSystem.h"
#include "../World/World.h"

void CollisionSystem::AddEntity(Entity entity, World& world) {
    if (world.positions.contains(entity) &&
        world.colliders.contains(entity)) {
        entities.insert(entity);
    }
}


void CollisionSystem::update(World& world, Quadtree& quadtree) {
    quadtree.clear();

    for (auto const& entity : entities) {
        auto& position = world.positions[entity];
        auto& collider = world.colliders[entity];
        auto& size = world.sizes[entity];

        collider.bounds = {
                position.x,
                position.y,
                size.width,
                size.height
        };

        quadtree.insert(entity, collider.bounds);
    }

    for (auto const& entity : entities) {
        if (!world.movementInputs.contains(entity)) continue;

        auto& position = world.positions[entity];
        auto& collider = world.colliders[entity];
        auto& size = world.sizes[entity];

        auto check = quadtree.retrieve(collider.bounds);

        bool grounded = false;

        for (const auto& [otherEntity, otherBounds] : check) {
            if (entity == otherEntity) continue;
            if (!world.colliders.contains(otherEntity)) continue;

            auto& otherCollider = world.colliders[otherEntity];
            if (!otherCollider.isStatic) continue;

            Velocity* velocity = nullptr;
            if (world.velocities.contains(entity)) {
                velocity = &world.velocities[entity];
            }

            if (world.springs.contains(otherEntity)) {
                if (!velocity) continue;
                const auto& spring = world.springs[otherEntity];
                resolveSpringCollision(position, velocity, collider.bounds, otherBounds, spring);
            } else {
                resolveWallCollision(position, velocity, collider.bounds, otherBounds);
                grounded = true;
            }
        }
        if (world.jumps.contains(entity)) {
            auto& jump = world.jumps[entity];
            jump.isGrounded = grounded;
        }
    }
}