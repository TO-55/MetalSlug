#include "Proyectil.hpp"

// Constructor que inicializa el proyectil con la posición y velocidad
Proyectil::Proyectil(float x, float y, float velocidad) {
    this->shape.setSize(sf::Vector2f(10.f, 5.f));  // Tamaño del proyectil
    this->shape.setPosition(x, y);                  // Posición inicial
    this->shape.setFillColor(sf::Color::Red);       // Color del proyectil
    this->shape.setOrigin(5.f, 2.5f);
    this->velocidad = velocidad;                    // Velocidad del proyectil
}

// Método para mover el proyectil en el eje X (hacia la derecha)
void Proyectil::mover() {
    shape.move(velocidad, 0);  // Mueve el proyectil en la dirección X
}

// Método para dibujar el proyectil en la ventana
void Proyectil::dibujar(sf::RenderWindow& window) {
    window.draw(shape);  // Dibuja el proyectil en la ventana
}

// Método para obtener los límites del proyectil (útil para detección de colisiones, por ejemplo)
sf::FloatRect Proyectil::obtenerLimites() const {
    return shape.getGlobalBounds();  // Retorna el rectángulo delimitador del proyectil
}
