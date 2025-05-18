#include "LevelState.h"
#include "../Game/controller.h"

LevelState::LevelState(sf::RenderWindow& renderWindow1, StateManager &stateManager1, float width1, float height1): renderWindow(renderWindow1), stateManager(stateManager1) {
    width = width1;
    height = height1;
}

void LevelState::draw() {

}

void LevelState::update() {
    ConcreteFactory concreteFactory(renderWindow);
    Controller controller1(width, height, renderWindow, stateManager);
    World world(controller1, concreteFactory, renderWindow);
    world.init();
    world.gameLoop();
}

void LevelState::init() {
}

void LevelState::inputController() {

}

