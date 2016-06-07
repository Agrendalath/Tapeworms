#ifndef TAPEWORMS_PLAYER_H
#define TAPEWORMS_PLAYER_H

#include "main.h"
#include "Obstacle.h"

class Player {
public:
    Player(int coord_multiplier);

    ~Player();

    void input();

    bool move(float rotation_value);

    bool handleObstacles();

    void createObstacle();

    sf::Vector2f *movement;
//    sf::Sprite *sprite;
    sf::CircleShape *sprite;
    std::vector<Obstacle> obstacles;
    int obstacles_map[WIDTH + 1][HEIGHT + 1]{};

private:
    void initialize(int coord_multiplier);

    bool collidesWithWall(sf::FloatRect coordinates);

    bool collidesWithObstacle(sf::FloatRect coordinates);

//    sf::Texture texture;

    sf::Color *color;

    bool placed_obstacle;

    bool should_place_obstacle;

    int collisions;

    void placeObstacles();

    sf::Vector2f obstaclePoint();

    void addPointToMap(sf::Vector2f position);

    // Time used for determining if user should leave obstacles
    time_t created, now;
};


#endif //TAPEWORMS_PLAYER_H
