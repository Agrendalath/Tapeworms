#ifndef TAPEWORMS_PLAYER_H
#define TAPEWORMS_PLAYER_H

#include "main.h"

class Player {
public:
    Player();

    ~Player();

    void input();

    void move(float rotation_value);

    sf::Vector2f *movement;
    sf::Sprite *sprite;

private:
    void initialize();

    bool playerHitWall(sf::Vector2f position);

    sf::Texture texture;
};


#endif //TAPEWORMS_PLAYER_H
