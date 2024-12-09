#ifndef CUERPO_DINAMICO_HPP
#define CUERPO_DINAMICO_HPP

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>

class CuerpoDinamico {
public:
    CuerpoDinamico(b2World& mundo, float posX, float posY, float radio, const std::string& texturaPath);
    void aplicarFuerza(float fuerzaX, float fuerzaY);
    void actualizarSprite(float ajusteAltura);
    sf::Sprite& obtenerSprite();
    b2Body* obtenerCuerpo();
    void controlarMovimiento(float fuerza, float fuerzaSalto, bool& enElSuelo, bool& mirandoALaDerecha, float ajusteAltura);

private:
    b2Body* cuerpo;
    sf::Texture textura;
    sf::Sprite sprite;
};

#endif // CUERPO_DINAMICO_HPP
