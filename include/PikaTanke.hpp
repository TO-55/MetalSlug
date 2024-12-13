#ifndef PIKATANKE_HPP
#define PIKATANKE_HPP

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>

enum ProjectileType {
    NORMAL,
    EXPLOSIVE,
    RAPID
};

struct Projectile {
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float damage;
    ProjectileType type;
};

class CuerpoDinamico {
public:
    CuerpoDinamico(b2World& mundo, float posX, float posY, float radio, const std::string& texturaPath);
    void aplicarFuerza(float fuerzaX, float fuerzaY);
    void actualizarSprite(float ajusteAltura);
    sf::Sprite& obtenerSprite();
    b2Body* obtenerCuerpo();
    void controlarMovimiento(float fuerza, float fuerzaSalto, bool& enElSuelo, bool& mirandoALaDerecha, float ajusteAltura, float limiteIzquierda, float limiteDerecha);

    // Shooting system
    void disparar(ProjectileType tipo = NORMAL);
    void actualizarProyectiles();
    void dibujarProyectiles(sf::RenderWindow& ventana);
    void checkProjectileCollisions(sf::FloatRect targetBounds); // For enemy collision

private:
    b2Body* cuerpo;
    sf::Texture textura;
    sf::Sprite sprite;

    std::vector<Projectile> proyectiles;
    int frameSinceLastShot = 0;
    const int framesPerShot = 15;
    bool mirandoALaDerecha = true;
};

#endif // PIKATANKE_HPP
