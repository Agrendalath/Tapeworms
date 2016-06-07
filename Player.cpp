#include "Player.h"

Player::Player(int coord_multiplier) {
    initialize(coord_multiplier);
}

Player::~Player() {
    while(!obstacles.empty())
        obstacles.pop_back();

    delete movement;
    delete sprite;
    delete color;
}

void Player::initialize(int coord_multiplier) {
//    obstacles_map = {0};
//    // Load texture
//    if(!texture.loadFromFile(app_resources + player_texture))
//        exit(-1);
//
//    // Convert texture to sprite
//    sprite = new sf::Sprite(texture);
    int radius = 2;
    sprite = new sf::CircleShape(radius);
//    sprite->setFillColor(sf::Color::Red);
    sprite->setOutlineColor(sf::Color::Red);
    sprite->setOrigin(radius, radius);
//    sprite->setOrigin(15, 8); // This will allow rotating around the center
    sprite->rotate(45);
    sprite->setPosition(10 * coord_multiplier, 10 * coord_multiplier);

    // Movement
    movement = new sf::Vector2f(1, 1);

    // Red line
    color = new sf::Color(255, 0, 0);

    time(&created);
}

// Move and rotate player
bool Player::move(float rotation_value) {
    sprite->rotate(rotation_value);
    float rotation = (float) (sprite->getRotation() * M_PI / 180);
    movement->x = (float) cos(rotation);
    movement->y = (float) sin(rotation);
    sprite->move(*movement);
    if(collidesWithWall(sprite->getGlobalBounds())) {
        sprite->move(-*movement);
        return false;
    }

    if(handleObstacles()) {
        sprite->move(-*movement);
        return false;
    }
    return true;
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
        for(int i = 0; i < 3; ++i)
            move(0);
    }

        // Relocate (debug purposes)
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        sprite->setPosition(300, 300);
    }
}

// Simple collisions, you can use getGlobalBounds() to check them accurately
bool Player::collidesWithWall(sf::FloatRect coordinates) {
    return (coordinates.left < 0 || coordinates.left + coordinates.width > WIDTH
            || coordinates.top < 0 || coordinates.top + coordinates.height > HEIGHT);
}

void Player::placeObstacles() {
    if(should_place_obstacle && !(rand() % 40))
        should_place_obstacle = false;

    else if(!(rand() % 20))
        should_place_obstacle = true;
}

bool Player::handleObstacles() {
    // No obstacles for 2 seconds
    time(&now);
    if(difftime(now, created) > 1)
        placeObstacles();

    if(!placed_obstacle && should_place_obstacle) {
        createObstacle();
        placed_obstacle = true;
    }
    else if(placed_obstacle && should_place_obstacle) {
        sf::Vector2f point = obstaclePoint();
        obstacles.back().addPoint(point, *color);
        addPointToMap(point);
    }
    else {
        placed_obstacle = false;
    }

    return collidesWithObstacle(sprite->getGlobalBounds());
}

void Player::createObstacle() {
    sf::Vector2f point = obstaclePoint();
    Obstacle *obstacle = new Obstacle(point, *color);
    obstacles.push_back(*obstacle);
    addPointToMap(point);
}

sf::Vector2f Player::obstaclePoint() {
    sf::Vector2f less(*movement);
    less.x *= 10;
    less.y *= 10;
    return sprite->getPosition() - less;
}

void Player::addPointToMap(sf::Vector2f position) {
    int x = (int) (position.x);
    int y = (int) (position.y);
    if(x <= WIDTH && y <= HEIGHT)
        obstacles_map[x][y] = 1;
}

bool Player::collidesWithObstacle(sf::FloatRect coordinates) {
    for(unsigned i = (unsigned) coordinates.left; i < coordinates.left + coordinates.width; ++i) {
        for(unsigned j = (unsigned) coordinates.top; j < coordinates.top + coordinates.height; ++j) {
            if(obstacles_map[i][j]) {
                ++collisions;
//                printf("BOOM %d\n", collisions);
                return true;
            }
        }
    }
    return false;
}
