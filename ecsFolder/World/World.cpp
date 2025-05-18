#include "World.h"

World::World(ControllerV &controllerV1, AbstractFactory &abstractFactory1, sf::RenderWindow& window1)
        : abstractFactory(abstractFactory1), controllerV(controllerV1), window(window1), stopwatch(std::make_shared<Stopwatch>())
{
    for (Entity id = 0; id < 200; ++id) {
        availableEntities.push(id);
    }
}

Entity World::createEntity() {
    Entity id = availableEntities.front();
    availableEntities.pop();
    return id;
}

void World::init() {
    renderSystem = std::make_shared<RenderSystem>();
    inputSystem = std::make_shared<InputSystem>();
    movementSystem = std::make_shared<MovementSystem>();
    physicsSystem = std::make_shared<PhysicsSystem>();
    collisionSystem = std::make_shared<CollisionSystem>();
    cameraSystem = std::make_shared<CameraSystem>();

    player = buildPlayer(200.f, 120.f, 20.f, 20.f);

    walls.push_back(buildWall(100, 100, 400, 40));
    walls.push_back(buildWall(600, 120, 100, 40));
    walls.push_back(buildWall(600, 300, 100, 40));

    springsE.push_back(buildSpring(400.f, 140.f, 20.f, 20.f));

    cameraSystem->init(window);
}

void World::update() {
    if (!stopwatch) return;

    this->stopwatch->nextFrame();
    float movementMul = this->stopwatch->getMovementMultiplier();

    if (inputSystem) inputSystem->update(*this);
    if (movementSystem) movementSystem->update(*this, movementMul);
    if (physicsSystem) physicsSystem->update(*this, movementMul);
    if (collisionSystem) collisionSystem->update(*this, collisionTree);
    if (cameraSystem) cameraSystem->update(*this, window, player);
    if (renderSystem) renderSystem->update(*this, window);
}

void World::gameLoop() {
    while (controllerV.isOpen() && window.isOpen()) {
        controllerV.checkForClose();

        window.clear(sf::Color::White);

        this->update();

        window.display();
    }
}

Entity World::buildPlayer(float x, float y, float width, float height) {
    Entity player = PlayerBuilder(*this, abstractFactory)
            .makePlayer(x, y, width, height)
            .build();

    if (collisionSystem) {
        collisionSystem->AddEntity(player, *this);
    }
    if (inputSystem) {
        inputSystem->AddEntity(player, *this);
    }
    if (movementSystem) {
        movementSystem->AddEntity(player, *this);
    }
    if (physicsSystem) {
        physicsSystem->AddEntity(player, *this);
    }

    return player;
}


Entity World::buildWall(float x, float y, float width, float height) {
    Entity wall = WallBuilder(*this, abstractFactory)
            .makeWall(x, y, width, height)
            .build();

    if (collisionSystem) {
        collisionSystem->AddEntity(wall, *this);
    }

    return wall;
}


Entity World::buildSpring(float x, float y, float width, float height) {
    Entity spring = SpringBuilder(*this, abstractFactory)
            .makeSpring(x, y, width, height)
            .build();

    if (collisionSystem) {
        collisionSystem->AddEntity(spring, *this);
    }

    return spring;
}

Entity World::buildSpike(float x, float y, float width, float height) {
    Entity spring = SpikeBuilder(*this, abstractFactory)
            .makeSpike(x, y, width, height)
            .build();

    if (collisionSystem) {
        collisionSystem->AddEntity(spring, *this);
    }

    return spring;
}

