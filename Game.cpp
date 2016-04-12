#include "Game.h"


Game::Game() {
    srand((unsigned int) time(NULL));
}

Game::~Game() {
    while(!players.empty())
        players.pop_back();

    delete text;
    delete window;
}

void Game::initialize() {
    // Create window
    window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), app_name);
    window->setFramerateLimit(60);

    // Load font and display the title
    if(!font.loadFromFile(app_resources + app_font))
        exit(-1);
    text = new sf::Text(app_name, font, 50);
    text->setPosition(WIDTH / 2 - text->getGlobalBounds().width / 2, 0);
//    text->setPosition(0, 0);

    create_players();
}

void Game::create_players() {
    for(int i = 0; i < NUMBER_OF_PLAYERS; ++i) {
        Player *player = new Player();
        players.push_back(*player);
    }
}

// Main loop
void Game::play() {
    initialize();

    while(window->isOpen() && !END) {
        input();
        for(Player &player: players) {
            player.input();
        }

        sf::Event event;
        while(window->pollEvent(event)) {
            switch(event.type) {

                // Handle miscellaneous key presses
                case sf::Event::KeyPressed:
                    // Handle debug
                    if(event.key.code == sf::Keyboard::D) {
                        DEBUG = !DEBUG;
                        if(!DEBUG) {
                            std::string message = app_name;
                            text->setString(message);
                        }
                    }
                    break;


                    // Handle SIGINT
                case sf::Event::Closed:
                    window->close();
                    break;

                default:
                    break;
            }
        }

        for(Player &player: players) {
            if(!player.move(0)) {
                END = true;
                text->setString("GAME OVER");
                display();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
        display();
    }
}

void Game::display() {
    if(DEBUG) {
        int x = (int) players[0].sprite->getPosition().x, y = (int) players[0].sprite->getPosition().y;
//        std::string message = "X: " + std::to_string(x) + " Y: " + std::to_string(y);
        int a = (int) players[0].sprite->getGlobalBounds().left, b = (int) players[0].sprite->getGlobalBounds().top;
        std::string message = "X: " + std::to_string(x) + " " + std::to_string(a) + " Y: " + std::to_string(y) + " " + std::to_string(b);
//        message += "Left: " + std::to_string(a) + " Top: " + std::to_string(b);
        text->setString(message);
    }

    window->clear();
    for(Player &player: players) {
        window->draw(*player.sprite);
        for(Obstacle &obstacle: player.obstacles) {
            window->draw(*obstacle.line);
        }
    }
    window->draw(*text);
    window->display();
}

// Handle keyboard events - used outside of game events to prevent delays
void Game::input() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        window->close();
}
