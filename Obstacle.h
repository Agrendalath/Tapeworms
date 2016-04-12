#ifndef TAPEWORMS_OBSTACLE_H
#define TAPEWORMS_OBSTACLE_H


#include <SFML/System.hpp>
#include "main.h"

class Obstacle {
public:
    Obstacle();

    Obstacle(sf::Vector2f const &start, sf::Color const &color);

    ~Obstacle();

    void addPoint(sf::Vector2f const &point, sf::Color const &color);

    sf::VertexArray *line;

private:

};


#endif //TAPEWORMS_OBSTACLE_H