#ifndef INDIVIDUALPLATFORMER_COMPONENTS_H

#include <string>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include <iostream>

#define INDIVIDUALPLATFORMER_COMPONENTS_H

using namespace std;

struct Collider {
    sf::FloatRect bounds;
    bool isStatic = false;
};

struct Transform {
    sf::Vector2f position;
};

struct Gravity {
    float force = 0.2f;
};

struct Jump {
    float impulse = 6.f;
    bool isGrounded = false;
};

struct Spring {
    float bounceImpulse = 12.f;
};

struct MovementInput {
    bool right = false;
    bool left = false;
    bool jump = false;
    bool wasJumping = false;
};

struct Position {
    float x;
    float y;
};

struct Size {
    float width;
    float height;
};

struct Velocity {
    float dx = 0;
    float dy = 0;
    float maxSpeed = 5.f;
    float acceleration = 300.f;
    float deceleration = 4.f;
};

struct Renderable {
    sf::RectangleShape shape;
    std::shared_ptr<sf::Texture> texture;

    Renderable() = default;

    explicit Renderable(sf::Vector2f size, sf::Color color = sf::Color::White) {
        shape.setSize(size);
        shape.setFillColor(color);
    }

    explicit Renderable(sf::Vector2f size, const std::string& texturePath) {
        shape.setSize(size);

        texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile(texturePath)) {
            shape.setFillColor(sf::Color::Magenta);
        } else {
            shape.setTexture(texture.get());
        }
    }
};

struct PlayerTag {};

struct WallTag {};

struct SpringTag {};

struct SpikeTag {};

#endif //INDIVIDUALPLATFORMER_COMPONENTS_H
