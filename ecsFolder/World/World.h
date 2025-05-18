#ifndef INDIVIDUALPLATFORMER_WORLD_H

#include <memory>
#include <queue>
#include "../Factories/AbstractFactory.h"
#include "./Stopwatch.h"
#include "../Game/ControllerV.h"
#include "../System/Types.h"
#include "../Components/Components.h"
#include "../Builder/PlayerBuilder.h"
#include "../Builder/WallBuilder.h"
#include "../Builder/SpringBuilder.h"
#include "../Builder/SpikeBuilder.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/InputSystem.h"
#include "../Systems/PhysicsSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/CameraSystem.h"
#include "../Collision/Quadtree.h"

#define INDIVIDUALPLATFORMER_WORLD_H

class World {
private:
    ControllerV& controllerV;
    AbstractFactory& abstractFactory;
    sf::RenderWindow& window;

    shared_ptr<RenderSystem> renderSystem;
    shared_ptr<InputSystem> inputSystem ;
    shared_ptr<MovementSystem> movementSystem;
    shared_ptr<PhysicsSystem> physicsSystem;
    shared_ptr<CollisionSystem> collisionSystem;
    shared_ptr<CameraSystem> cameraSystem;

    Quadtree collisionTree{0, sf::FloatRect(0, 0, 1200, 600)};

    std::shared_ptr<Stopwatch> stopwatch = Stopwatch::getInstance();
    Entity player;
    std::vector<Entity> walls;
    std::vector<Entity> springsE;
    queue<Entity> availableEntities;

public:
    World(ControllerV& controllerV, AbstractFactory& abstractFactory1, sf::RenderWindow& window1);

    void init();
    void gameLoop();
    void update();

    Entity buildPlayer(float x, float y, float width, float height);
    Entity buildWall(float x, float y, float width, float height);
    Entity buildSpring(float x, float y, float width, float height);
    Entity buildSpike(float x, float y, float width, float height);

    Entity createEntity();

    std::unordered_map<Entity, Position> positions;
    std::unordered_map<Entity, Size> sizes;
    std::unordered_map<Entity, Renderable> renderables;
    std::unordered_map<Entity, Velocity> velocities;
    std::unordered_map<Entity, Collider> colliders;
    std::unordered_map<Entity, Gravity> gravities;
    std::unordered_map<Entity, MovementInput> movementInputs;
    std::unordered_map<Entity, Jump> jumps;
    std::unordered_map<Entity, Transform> transforms;
    std::unordered_map<Entity, PlayerTag> playerTags;
    std::unordered_map<Entity, WallTag> wallTags;
    std::unordered_map<Entity, SpringTag> springTags;
    std::unordered_map<Entity, SpikeTag> spikeTags;
};

#endif //INDIVIDUALPLATFORMER_WORLD_H
