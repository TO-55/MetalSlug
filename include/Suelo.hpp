#ifndef SUELO_HPP
#define SUELO_HPP

#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

class Suelo {
public:
    Suelo(b2World& mundo, float posX, float posY, float width, float height);
    void dibujar(sf::RenderWindow& ventana);
    b2Body* obtenerCuerpo();

private:
    b2Body* cuerpo;
    sf::RectangleShape formaSuelo;
};

#endif // SUELO_HPP
