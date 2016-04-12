#ifndef TAPEWORMS_PLAYER_H
#define TAPEWORMS_PLAYER_H

#include "main.h"
#include "Obstacle.h"

class Player {
public:
    Player();

    ~Player();

    void input();

    void move(float rotation_value);

    void handleObstacles();

    void createObstacle();

    sf::Vector2f *movement;
    sf::Sprite *sprite;
    std::vector<Obstacle> obstacles;

private:
    void initialize();

    bool playerHitWall(sf::Vector2f position);

    sf::Texture texture;

    sf::Color *color;

    bool place_obstacle;

    int collisions;
};


#endif //TAPEWORMS_PLAYER_H
