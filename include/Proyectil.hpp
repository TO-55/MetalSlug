#ifndef PROYECTIL_HPP
#define PROYECTIL_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Proyectil {
public:
    // Constructor para crear un proyectil en una posición determinada
    Proyectil(float x, float y, float velocidad);

    // Método para mover el proyectil
    void mover();

    // Método para dibujar el proyectil
    void dibujar(sf::RenderWindow& ventana);

    // Método para obtener el rectángulo delimitador
    sf::FloatRect obtenerLimites() const;

    void setPosition(float x, float y) {
        shape.setPosition(x, y);
    }

    bool estaActivo() const { return activo;}
    void desactivar() { activo = false; }
    void reiniciar(float x, float y, float velocidad) {
        //reinicia posicion y estado
        setPosition(x, y);
        this->velocidad = velocidad;
        activo = true;
    }

private:
    bool activo = true;
    sf::RectangleShape shape; // Forma del proyectil
    float velocidad; // Velocidad del proyectil
};

#endif // PROYECTIL_HPP
