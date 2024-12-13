#ifndef PIKATANKE_HPP
#define PIKATANKE_HPP

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "Proyectil.hpp"

class CuerpoDinamico {
public:
    CuerpoDinamico(b2World& mundo, float posX, float posY, float radio, const std::string& texturaPath);
    void aplicarFuerza(float fuerzaX, float fuerzaY);
    void actualizarSprite(float ajusteAltura);
    sf::Sprite& obtenerSprite();
    b2Body* obtenerCuerpo();
    void controlarMovimiento(float fuerza, float fuerzaSalto, bool& enElSuelo, bool& mirandoALaDerecha, float ajusteAltura, float limiteIzquierda, float limiteDerecha);

    //Disparar
    void disparar();
    void actualizarProyectiles();
    void dibujarProyectiles(sf::RenderWindow& ventana);

private:
    b2Body* cuerpo;
    sf::Texture textura;
    sf::Sprite sprite;

    std::vector<sf::CircleShape> proyectiles;
    std::vector<sf::Vector2f> velocidadesProyectiles;
    float tiempoEntreDisparos = 0.5f; //segundos entre disparos
    sf::Clock relojDisparo;
    bool mirandoALaDerecha = true;
    sf::Clock relojProyectil;
    float tiempoEntreFrames = 60.f;
};

#endif // PIKATANKE_HPP
