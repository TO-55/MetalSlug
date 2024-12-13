#ifndef TARGET_HPP
#define TARGET_HPP  

#include <SFML/Graphics.hpp>
#include<iostream>

class Target {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    int health;
    bool alive;

public:
    Target();
    bool isAlive() const;
    void takeDamage();
    sf::FloatRect getBounds() const;
    void draw(sf::RenderWindow& window);
};

#endif // TARGET_HPP