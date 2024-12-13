#include "Charizardd.hpp"

Lagarto::Lagarto(const std::string& texturaPath, float posX, float posY, float limiteSup, float limiteInf, float scaleX, float scaleY) {
    // Load texture and set up sprite
    textura.loadFromFile(texturaPath);
    sprite.setTexture(textura);
    sprite.setPosition(posX, posY);
    sprite.setScale(scaleX, scaleY);

    // Initialize movement parameters
    y1 = posY ;           // Lower boundary
    y2 = posY - 200;  // Upper boundary (200 pixels above starting position)
    velocidad = sf::Vector2f(0.0f, -3.0f);  // Only vertical movement, starting upward
    moviendoDerecha = true;  // In this case, we'll use this to track if moving up
    enEspera = false;
    tiempoEspera = sf::seconds(1.0f);  // Wait time at top and bottom
}

void Lagarto::actualizar() {
    if (enEspera) {
        manejarEspera();
        return;
    }

    // Get current position
    sf::Vector2f posicion = sprite.getPosition();

    // Move the sprite
    sprite.move(velocidad);

    // Check boundaries and change direction
    if (moviendoDerecha && posicion.y <= y2) {  // Reached upper limit
        velocidad.y = 3.0f;  // Start moving down
        moviendoDerecha = false;
        enEspera = true;
        relojEspera.restart();
    }
    else if (!moviendoDerecha && posicion.y >= y1) {  // Reached lower limit
        velocidad.y = -3.0f;  // Start moving up
        moviendoDerecha = true;
        enEspera = true;
        relojEspera.restart();
    }
}

void Lagarto::manejarEspera() {
    if (relojEspera.getElapsedTime() >= tiempoEspera) {
        enEspera = false;
    }
}

void Lagarto::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(sprite);
}
