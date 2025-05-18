#include "RenderSystem.h"
#include "../World/World.h"

void RenderSystem::update(World& world, sf::RenderWindow& window) {
    window.clear(sf::Color::White);
    for (auto &[entity, renderable]: world.renderables) {
        if (world.positions.find(entity) != world.positions.end()) {
            auto &pos = world.positions[entity];
            renderable.shape.setPosition(
                    pos.x,
                    window.getSize().y - pos.y - renderable.shape.getSize().y
            );
            window.draw(renderable.shape);
        }
    }
};