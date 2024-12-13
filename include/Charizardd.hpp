#ifndef CHARIZARD_HPP
#define CHARIZARD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

class Lagarto {
public:
    Lagarto(const std::string& texturaPath, float posX, float posY, float limiteSup, float limiteInf, float scaleX, float scaleY);
    void actualizar(); // Actualiza el estado del personaje
    void dibujar(sf::RenderWindow& ventana); // Dibuja el personaje en la ventana
    bool estaVivo() const {return health > 0;}
    void takeDamage() {health--;}

private:

    int health = 5;

    sf::Sprite sprite; // Sprite del personaje
    sf::Texture textura; // Textura asociada al sprite

    float y1 = 275; // Límite inferior de movimiento
    float y2; // Límite superior de movimiento
    sf::Vector2f velocidad; // Velocidad de movimiento
    sf::Clock relojEspera; // Reloj para manejar tiempos de espera
    sf::Time tiempoEspera; // Duración del tiempo de espera
    bool moviendoDerecha; // Indica si el personaje se mueve hacia la derecha
    bool enEspera; // Indica si el personaje está en espera

    void manejarEspera(); // Maneja el tiempo de espera
};

#endif // CHARIZARD_HPP
