#ifndef VENTANA_HPP
#define VENTANA_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Ventana {
public:
    Ventana(int width, int height, const std::string& title);
    float getDeltaTime() {return deltaTime;}
    void cargarTextura(const std::string& filepath);
    void dibujarFondo();
    void dibujarSprite(const sf::Sprite& sprite);
    void actualizar();
    void mostrar();
    bool estaAbierta() const;
    sf::RenderWindow& obtenerVentana();
    const sf::Sprite& obtenerFondo() const; // Añadir este método

private:
    sf::RenderWindow window;
    sf::Texture texture;
    sf::Sprite spriteFondo;
    sf::Clock gameClock;
    float deltaTime;
};

#endif // VENTANA_HPP
