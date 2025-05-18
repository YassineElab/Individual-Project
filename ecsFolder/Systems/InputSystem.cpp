#include "InputSystem.h"
#include "../World/World.h"

void InputSystem::update(World& world) {
    for (auto entity : entities) {
        auto& input = world.movementInputs[entity];
        input.left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        input.right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        input.jump = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    }
}

void InputSystem::AddEntity(Entity entity, World& world) {
    if (world.movementInputs.contains(entity)) {
        entities.insert(entity);
    }
}