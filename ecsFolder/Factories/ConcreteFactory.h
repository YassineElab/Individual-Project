#ifndef INDIVIDUALPLATFORMER_CONCRETEFACTORY_H
#define INDIVIDUALPLATFORMER_CONCRETEFACTORY_H

#include "AbstractFactory.h"
#include "../Components/Components.h"
#include <SFML/Graphics.hpp>

class ConcreteFactory : public AbstractFactory {
private:
    sf::RenderWindow& window;

public:
    explicit ConcreteFactory(sf::RenderWindow& window);

    Entity createPlayer(World& world, float x, float y, float width, float height) override;
    Entity createWall(World& world, float x, float y, float width, float height) override;
    Entity createSpring(World& world, float x, float y, float width, float height) override;
    Entity createSpike(World& world, float x, float y, float width, float height) override;
};

#endif //INDIVIDUALPLATFORMER_CONCRETEFACTORY_H
