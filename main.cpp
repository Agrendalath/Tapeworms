#include <SFML/Graphics.hpp>
#include <cstdio>
#include <chrono>
#include <thread>
#define _USE_MATH_DEFINES // Windows OS requires that
#define WIDTH 600
#define HEIGHT 600
#define ROT 5


// Simple collisions, you can use getGlobalBounds() to check them accurately
bool playerHitWall(sf::Vector2f position) {
    return (position.x < 0 || position.y < 0 || position.x > WIDTH || position.y > HEIGHT);
}


// Move and rotate player
void move (sf::Sprite *sprite, sf::Vector2f *movement, float rotation_value) {
    sprite->rotate(rotation_value);
    float rotation = sprite->getRotation() * M_PI/180;
    movement->x = cos(rotation);
    movement->y = sin(rotation);
    sprite->move(*movement);
    if (playerHitWall(sprite->getPosition())) {
        sprite->move(-*movement);
    }
}


// Handle keyboard events - used outside of game events to prevent delays
void handle_keys (sf::Window *window, sf::Sprite *sprite, sf::Vector2f *movement) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        move(sprite, movement, -ROT);
        std::this_thread::sleep_for(std::chrono::milliseconds(25)); // Turning repeatedly won't now result in overall velocity boost
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        move(sprite, movement, ROT);
        std::this_thread::sleep_for(std::chrono::milliseconds(25)); // Turning repeatedly won't now result in overall velocity boost
    }

    // DEBUG speed up
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        move(sprite, movement, 0);
        move(sprite, movement, 0);
        move(sprite, movement, 0);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        window->close();
}


// Display board
void display(sf::RenderWindow *window, sf::Sprite *sprite, sf::Text *text, bool *DEBUG) {
    if (*DEBUG) {
        int x = sprite->getPosition().x, y = sprite->getPosition().y;
        std::string message = "X: " + std::to_string(x) + " Y: " + std::to_string(y);
        text->setString(message);
    }

    window->clear();
    window->draw(*sprite);
    window->draw(*text);
    window->display();
}


int main() {
    std::string app_name = "Tapeworms";
    std::string app_resources = "../../sfml/Tapeworms/Resources/";

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), app_name);
    window.setFramerateLimit(60);

    // Title
    sf::Font font;
    if (!font.loadFromFile(app_resources + "arial.ttf"))
        exit(-1);
    sf::Text text(app_name, font, 50);
    text.setPosition(WIDTH/2-text.getGlobalBounds().width/2, 0);

    // Arrow
    sf::Texture texture;
    if (!texture.loadFromFile(app_resources + "arrow.png"))
        exit(-1);
    sf::Sprite sprite(texture);
    sprite.setOrigin(15, 8); // This will allow rotating around the center
    sprite.rotate(45);
    sprite.setPosition(0, 0);

    // Movement
    sf::Vector2f movement(1,1);

    // Debug state
    bool DEBUG = false;

    // Main loop
    while (window.isOpen()) {
        handle_keys(&window, &sprite, &movement);

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {

            // Handle miscelanous key presses
            case sf::Event::KeyPressed:
                // Handle debug
                if (event.key.code == sf::Keyboard::D) {
                    DEBUG = !DEBUG;
                    if (!DEBUG) {
                        std::string message = "Tapeworms";
                        text.setString(message);
                    }
                }
                // Teleport (don't ask, just debug purposes)
                else if (event.key.code == sf::Keyboard::A) {
                    sprite.setPosition(300, 300);
                }
                break;


            // Handle SIGINT
            case sf::Event::Closed:
                window.close();
                break;

            default:
                break;
            }
        }

        move(&sprite, &movement, 0);
        display(&window, &sprite, &text, &DEBUG);
    }

    return 0;
}
