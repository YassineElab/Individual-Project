#ifndef INDIVIDUALPLATFORMER_COLLISIONSYSTEM_H

#include "../System/Types.h"
#include "../System/System.h"
#include "../Components/Components.h"
#include "../Collision/Quadtree.h"
#include <SFML/Graphics.hpp>

#define INDIVIDUALPLATFORMER_COLLISIONSYSTEM_H

class World;

class CollisionSystem : public System {
private:
    void resolveWallCollision(Position& position, Velocity* velocity,
                          const sf::FloatRect& player, const sf::FloatRect& wall) {
        sf::FloatRect intersection;
        if (!player.intersects(wall, intersection)) return;

        if (intersection.width < intersection.height) {
            position.x += (player.left < wall.left) ? -intersection.width : intersection.width;
            if (velocity) velocity->dx = 0;
        } else {
            bool hitFromAbove = player.top < wall.top;
            position.y += hitFromAbove ? -intersection.height : intersection.height;
            if (velocity) velocity->dy = 0;
        }
    }


    void resolveSpringCollision(Position& position, Velocity* velocity,
                                const sf::FloatRect& player, const sf::FloatRect& springBounds,
                                const Spring& spring) {
        sf::FloatRect intersection;
        if (!player.intersects(springBounds, intersection)) return;

        if (velocity) {
            if (intersection.width < intersection.height) {
                position.x += (player.left < springBounds.left) ? -intersection.width : intersection.width;
            } else {
                position.y += (player.top < springBounds.top) ? -intersection.height : intersection.height;
            }
            velocity->dy = spring.bounceImpulse;
        }
    }

public:
    void AddEntity(Entity entity, World& world);

    void update(World& world, Quadtree& quadtree);
};

#endif //INDIVIDUALPLATFORMER_COLLISIONSYSTEM_H