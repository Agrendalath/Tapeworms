#ifndef TAPEWORMS_PLAYER_H
#define TAPEWORMS_PLAYER_H

#include "main.h"
#include "Obstacle.h"

class Player {
public:
    Player();

    ~Player();

    void input();

    bool move(float rotation_value);

    bool handleObstacles();

    void createObstacle();

    sf::Vector2f *movement;
//    sf::Sprite *sprite;
    sf::CircleShape *sprite;
    std::vector<Obstacle> obstacles;
    int obstacles_map[WIDTH+1][HEIGHT+1];

private:
    void initialize();

    bool playerHitWall(sf::Vector2f position);

//    sf::Texture texture;

    sf::Color *color;

    bool placed_obstacle;

    bool should_place_obstacle;

    int collisions;

    void placeObstacles();
};


#endif //TAPEWORMS_PLAYER_H
