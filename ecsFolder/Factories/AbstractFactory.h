#ifndef INDIVIDUALPLATFORMER_ABSTRACTFACTORY_H

#include "../System/Types.h"

#define INDIVIDUALPLATFORMER_ABSTRACTFACTORY_H

class World;

class AbstractFactory {
public:
    virtual Entity createPlayer(World& world, float x, float y, float width, float height) = 0;
    virtual Entity createWall(World& world, float x, float y, float width, float height) = 0;
    virtual Entity createSpring(World& world, float x, float y, float width, float height) = 0;
    virtual ~AbstractFactory() = default;
};

#endif //INDIVIDUALPLATFORMER_ABSTRACTFACTORY_H
