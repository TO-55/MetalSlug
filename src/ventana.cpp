#include "Ventana.hpp"
#include <iostream>

Ventana::Ventana(int width, int height, const std::string& title)
    {
    window.create(sf::VideoMode(width, height), title);
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);
    deltaTime = 0.0f;
    }

void Ventana::cargarTextura(const std::string& filepath) {
    if (!texture.loadFromFile(filepath)) {
        std::cerr << "Error al cargar la textura" << std::endl;
        exit(-1);
    }
    spriteFondo.setTexture(texture);

    // Quitar el ajuste de escala para mantener el tamaño original del fondo
}

void Ventana::actualizar() {
    deltaTime = gameClock.restart().asSeconds();

    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Ventana::dibujarFondo() {
    window.clear();
    window.draw(spriteFondo);
}

void Ventana::dibujarSprite(const sf::Sprite& sprite) {
    window.draw(sprite);
}




void Ventana::mostrar() {
    window.display();
}

bool Ventana::estaAbierta() const {
    return window.isOpen();
}

sf::RenderWindow& Ventana::obtenerVentana() {
    return window;
}

const sf::Sprite& Ventana::obtenerFondo() const {
    return spriteFondo;
}
