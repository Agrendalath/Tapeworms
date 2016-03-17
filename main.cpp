#include <SFML/Graphics.hpp>
#include <cstdio>
#define ROT 5

// Rotate player
void rotate (sf::Sprite *sprite, sf::Vector2f *movement, float rotation_value) {
    sprite->rotate(rotation_value);
    float rotation = sprite->getRotation() * M_PI/180;
    movement->x = cos(rotation);
    movement->y = sin(rotation);
    sprite->move(*movement);
}


// Handle keyboard events - used outside of game events to prevent delays
void handle_keys (sf::Window *window, sf::Sprite *sprite, sf::Vector2f *movement) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        rotate(sprite, movement, -5);

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        rotate(sprite, movement, 5);

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        window->close();
}


// Refresh board
void display(sf::RenderWindow *window, sf::Sprite *sprite, sf::Text *text) {
    window->clear();
    window->draw(*sprite);
    window->draw(*text);
    window->display();
}


int main() {
    std::string app_name = "Tapeworms";
    std::string app_resources = "../../sfml/Tapeworms/Resources/";

    sf::RenderWindow window(sf::VideoMode(600, 600), app_name);
    window.setFramerateLimit(60);

    // Title
    sf::Font font;
    if (!font.loadFromFile(app_resources + "arial.ttf"))
        exit(-1);
    sf::Text text(app_name, font, 50);

    // Arrow
    sf::Texture texture;
    if (!texture.loadFromFile(app_resources + "arrow.png"))
        exit(-1);
    sf::Sprite sprite(texture);
    sprite.rotate(45);

    // Movement
    sf::Vector2f movement(1,1);


    // Main loop
    while (window.isOpen()) {
        handle_keys(&window, &sprite, &movement);

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            // Handle SIGINT
            case sf::Event::Closed:
                window.close();
                break;

            default:
                break;
            }
        }

        rotate(&sprite, &movement, 0);
        display(&window, &sprite, &text);
    }

    return 0;
}
