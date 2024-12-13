// Personaje.cpp
#include "Meowth.hpp"
#include <iostream>

Personaje::Personaje(const std::string& texturaPath, float posX, float posY, float limiteIzq, float limiteDer, float scaleX, float scaleY)
    : x1(limiteIzq), x2(limiteDer), velocidad(2.f, 0.f), tiempoEspera(sf::seconds(0.5f)), moviendoDerecha(true), enEspera(false) {

    if (!textura.loadFromFile(texturaPath)) {
        std::cerr << "Error al cargar la textura" << std::endl;
        exit(-1);
    }

    sprite.setTexture(textura);

    sprite.setOrigin(textura.getSize().x / 2.f, textura.getSize().y / 2.f);

    sprite.setScale(scaleX,scaleY);

    sprite.setPosition(posX, posY);
   
   
}

void Personaje::actualizar() {
    if (!enEspera) {
        sprite.move(velocidad);

        if (moviendoDerecha && sprite.getPosition().x >= x2) {
            sprite.setPosition(x2, sprite.getPosition().y);
            moviendoDerecha = false;
            velocidad.x = -velocidad.x;
            sprite.setScale(-.2f, .2f);
            enEspera = true;
            relojEspera.restart();
        } else if (!moviendoDerecha && sprite.getPosition().x <= x1) {
            sprite.setPosition(x1, sprite.getPosition().y);
            moviendoDerecha = true;
            velocidad.x = -velocidad.x;
            sprite.setScale(.2f, .2f);
            enEspera = true;
            relojEspera.restart();
        }
    } else {
        manejarEspera();
    }
}

void Personaje::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(sprite);
}

void Personaje::manejarEspera() {
    if (relojEspera.getElapsedTime() >= tiempoEspera) {
        enEspera = false;
    }
}
