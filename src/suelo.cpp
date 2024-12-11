#include "suelo.hpp"

Suelo::Suelo(b2World& mundo, float posX, float posY, float width, float height) {
    // Definir el cuerpo del suelo
    b2BodyDef cuerpoSueloDef;
    cuerpoSueloDef.position.Set(posX, posY);
    cuerpo = mundo.CreateBody(&cuerpoSueloDef);

    // Definir la forma del suelo en Box2D
    b2PolygonShape formaSueloBox2D;
    formaSueloBox2D.SetAsBox(width / 2.0f, height / 2.0f);

    // Crear la fixture del suelo en Box2D
    b2FixtureDef fixtureSueloDef;
    fixtureSueloDef.shape = &formaSueloBox2D;
    fixtureSueloDef.friction = 1.0f;
    cuerpo->CreateFixture(&fixtureSueloDef);

    // Definir la forma del suelo en SFML
    formaSuelo.setSize(sf::Vector2f(width, height));
    formaSuelo.setOrigin(width / 2.0f, height / 2.0f);
    formaSuelo.setPosition(posX, posY);
    formaSuelo.setFillColor(sf::Color::White);  // Asegurar que el color es blanco
}

void Suelo::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(formaSuelo);
}

b2Body* Suelo::obtenerCuerpo() {
    return cuerpo;
}
