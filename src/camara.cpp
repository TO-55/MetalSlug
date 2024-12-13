#include "Camara.hpp"

Camara::Camara(sf::RenderWindow& ventana, float velocidad, const sf::Sprite& fondo) : ventana(ventana), velocidad(velocidad) {
    vista = ventana.getView();
    limites = fondo.getGlobalBounds();
}

void Camara::actualizar() {
    ventana.setView(vista);
}

void Camara::moverIzquierda() {
    if (vista.getCenter().x - vista.getSize().x / 2 > limites.left) {
        vista.move(-velocidad, 0);
        // Asegurarse de no pasar el límite izquierdo
        if (vista.getCenter().x - vista.getSize().x / 2 < limites.left) {
            vista.setCenter(limites.left + vista.getSize().x / 2, vista.getCenter().y);
        }
    }
}

void Camara::moverDerecha() {
    if (vista.getCenter().x + vista.getSize().x / 2 < limites.left + limites.width) {
        vista.move(velocidad, 0);
        // Asegurarse de no pasar el límite derecho
        if (vista.getCenter().x + vista.getSize().x / 2 > limites.left + limites.width) {
            vista.setCenter(limites.left + limites.width - vista.getSize().x / 2, vista.getCenter().y);
        }
    }
}

sf::View& Camara::obtenerVista() {
    return vista;
}
