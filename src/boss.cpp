#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

int main()
{
    // Crear la ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mi Personaje en SFML");

    // Cargar la textura del personaje
    sf::Texture texture;
    if (!texture.loadFromFile("./assets/images/Blastoise_MS2.png")) {
        return -1;
    }

    // Crear el sprite del personaje
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(800, 300); // Posicionar el sprite en el centro de la ventana
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2); // Establecer el origen en el centro

    // Variables de física
    float x1 = 100.f; // Punto inicial
    float x2 = 700.f; // Punto final
    sf::Vector2f velocity(0.1f, 0.f); // Velocidad inicial del personaje más lenta
    sf::Vector2f acceleration(0.f, 0.0008f); // Aceleración/gravedad reducida para saltos lunares
    bool movingRight = true; // Dirección inicial
    sf::Clock clock;
    sf::Time waitTime = sf::seconds(0.5f); // Tiempo de espera reducido a 0.5 segundos
    bool waiting = false;

    // Reloj para el salto
    sf::Clock jumpClock;
    sf::Time jumpInterval = sf::seconds(1.f); // Intervalo de tiempo para saltar
    bool jumping = false; // Estado del salto

    // Bucle principal
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Manejar el salto
        if (!jumping && jumpClock.getElapsedTime() >= jumpInterval)
        {
            velocity.y = -0.75f; // Fuerza hacia arriba reducida para saltos más lentos
            jumping = true; // Activar estado de salto
            jumpClock.restart(); // Reiniciar el reloj de salto
        }

        // Actualizar la física
        velocity += acceleration; // Aplicar la aceleración a la velocidad
        sprite.move(velocity); // Mover el sprite según la velocidad

        // Limitar al personaje dentro de la ventana
        if (sprite.getPosition().y + sprite.getGlobalBounds().height / 2 > window.getSize().y)
        {
            sprite.setPosition(sprite.getPosition().x, window.getSize().y - sprite.getGlobalBounds().height / 2);
            velocity.y = 0; // Resetear la velocidad vertical al tocar el suelo
            jumping = false; // Desactivar estado de salto
        }

        // Comprobar si ha llegado a x2 o x1
        if (!waiting)
        {
            if (movingRight && sprite.getPosition().x >= x2)
            {
                sprite.setPosition(x2, sprite.getPosition().y);
                movingRight = false;
                velocity.x = -velocity.x; // Invertir la dirección
                sprite.setScale(-1.f, 1.f); // Mirar a la izquierda
                waiting = true;
                clock.restart(); // Reiniciar el reloj
            }
            else if (!movingRight && sprite.getPosition().x <= x1)
            {
                sprite.setPosition(x1, sprite.getPosition().y);
                movingRight = true;
                velocity.x = -velocity.x; // Invertir la dirección
                sprite.setScale(1.f, 1.f); // Mirar a la derecha
                waiting = true;
                clock.restart(); // Reiniciar el reloj
            }
        }
        else
        {
            // Esperar durante el tiempo especificado
            if (clock.getElapsedTime() >= waitTime)
            {
                waiting = false; // Terminar de esperar
            }
        }

        window.clear();
        window.draw(sprite); // Dibujar el sprite del personaje
        window.display();
    }

    return 0;
}