#ifndef CAMARA_HPP
#define CAMARA_HPP

#include <SFML/Graphics.hpp>

class Camara {
public:
    Camara(sf::RenderWindow& ventana, float velocidad, const sf::Sprite& fondo);
    void actualizar();
    void moverIzquierda();
    void moverDerecha();
    void moverArriba();
    void moverAbajo();
    void seguirPersonaje(const sf::Sprite& personaje); // Nuevo método para seguir al personaje
    sf::View& obtenerVista();

private:
    sf::RenderWindow& ventana;
    sf::View vista;
    float velocidad;
    sf::FloatRect limites;
};

#endif // CAMARA_HPP
