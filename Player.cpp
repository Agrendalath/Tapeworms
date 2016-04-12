#include "Player.h"

Player::Player() {
    initialize();
}

Player::~Player() {
    delete movement;
    delete sprite;
}

void Player::initialize() {
    // Load texture
    if(!texture.loadFromFile(app_resources + player_texture))
        exit(-1);

    // Convert texture to sprite
    sprite = new sf::Sprite(texture);
    sprite->setOrigin(15, 8); // This will allow rotating around the center
    sprite->rotate(45);
    sprite->setPosition(0, 0);

    // Movement
    movement = new sf::Vector2f(1, 1);
}

// Move and rotate player
void Player::move(float rotation_value) {
    sprite->rotate(rotation_value);
    float rotation = (float) (sprite->getRotation() * M_PI / 180);
    movement->x = (float) cos(rotation);
    movement->y = (float) sin(rotation);
    sprite->move(*movement);
    if(playerHitWall((sprite->getPosition()))) {
        sprite->move(-*movement);
    }
}

// Handle keyboard events - used outside of game events to prevent delays
void Player::input() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        move(-ROT);
        std::this_thread::sleep_for(
                std::chrono::milliseconds(25)); // Turning repeatedly won't now result in overall velocity boost
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        move(ROT);
        std::this_thread::sleep_for(
                std::chrono::milliseconds(25)); // Turning repeatedly won't now result in overall velocity boost
    }

        // DEBUG speed up
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        move(0);
        move(0);
        move(0);
    }

        // Relocate (debug purposes)
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sprite->setPosition(300, 300);
    }
}

// Simple collisions, you can use getGlobalBounds() to check them accurately
bool Player::playerHitWall(sf::Vector2f position) {
    return (position.x < 0 || position.y < 0 || position.x > WIDTH || position.y > HEIGHT);
}