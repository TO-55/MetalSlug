#ifndef VENTANA_HPP
#define VENTANA_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Ventana {
public:
    Ventana(int width, int height, const std::string& title);
    void cargarTextura(const std::string& filepath);
    void dibujarFondo();
    void dibujarSprite(const sf::Sprite& sprite);
    void actualizar();
    bool estaAbierta() const;
    void mostrar();


private:
    sf::RenderWindow window;
    sf::Texture texture;
    sf::Sprite spriteFondo;
};

#endif // VENTANA_HPP
