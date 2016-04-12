#include "Obstacle.h"

Obstacle::Obstacle() {
}

Obstacle::Obstacle(sf::Vector2f const &start, sf::Color const &color) {
    line = new sf::VertexArray(sf::LinesStrip, 1);
    (*line)[0].position = start;
    (*line)[0].color = color;
}

Obstacle::~Obstacle() {
}

void Obstacle::addPoint(sf::Vector2f const &point, sf::Color const &color) {
    line->append(sf::Vertex(point, color));
}