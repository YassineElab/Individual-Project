#include "ConcreteFactory.h"
#include "../World/World.h"

ConcreteFactory::ConcreteFactory(sf::RenderWindow& window) : window(window) {}

Entity ConcreteFactory::createPlayer(World& world, float x, float y, float width, float height) {
    Entity player = world.createEntity();

    world.positions[player] = Position{x, y};
    world.gravities[player] = Gravity{};
    world.sizes[player] = Size{width, height};
    world.velocities[player] = Velocity{0.f, 0.f};
    world.renderables[player] = Renderable{{width, height}, sf::Color::Red};
    world.movementInputs[player] = MovementInput{};
    world.jumps[player] = Jump{};
    world.transforms[player] = Transform{.position = {x, y}};
    world.colliders[player] = Collider{
            .bounds = {x, y, width, height},
            .isStatic = false
    };
    world.playerTags.insert({player, PlayerTag{}});

    return player;
}

Entity ConcreteFactory::createWall(World& world, float x, float y, float width, float height) {
    Entity wall = world.createEntity();

    world.transforms[wall] = Transform{.position = {x, y}};
    world.colliders[wall] = Collider{
            .bounds = {x, y, width, height},
            .isStatic = true
    };
    world.positions[wall] = Position{x, y};
    world.sizes[wall] = Size{width, height};
    world.renderables[wall] = Renderable{{width, height}, sf::Color::Blue};
    world.wallTags.insert({wall, WallTag{}});

    return wall;
}

Entity ConcreteFactory::createSpring(World& world, float x, float y, float width, float height) {
    Entity spring = world.createEntity();

    world.transforms[spring] = Transform{.position = {x, y}};
    world.positions[spring] = Position{x, y};
    world.sizes[spring] = Size{width, height};
    world.renderables[spring] = Renderable{{width, height}, sf::Color::Green};
    world.colliders[spring] = Collider{
            .bounds = {x, y, width, height},
            .isStatic = true
    };
    world.springs[spring] = Spring{};
    world.springTags.insert({spring, SpringTag{}});

    return spring;
}
