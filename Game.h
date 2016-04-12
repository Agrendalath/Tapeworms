#ifndef TAPEWORMS_GAME_H
#define TAPEWORMS_GAME_H

#include "main.h"
#include "Player.h"
#include <vector>

class Game {
public:
    Game();

    ~Game();

    void play();

    sf::RenderWindow *window;
    sf::Text *text;
private:
    void initialize();

    void create_players();

    void display();

    void input();

    sf::Font font;
    std::vector<Player> players;

    // Debug state
    bool DEBUG = false;
};


#endif //TAPEWORMS_GAME_H