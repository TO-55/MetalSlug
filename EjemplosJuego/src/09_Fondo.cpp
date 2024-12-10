#include <SFML/Graphics.hpp>

int main()
{
 // Crear una ventana de SFML
    sf::RenderWindow window(sf::VideoMode(2022,211), "SFML works!");

    sf::;
    if (!texture.loadFromFile("./assets/images/mapa.png"))
    {
        // Manejar el error si no se puede cargar la imagen
        return -1;
    }

    // Crear un sprite y asignarle la textura
    sf::Sprite sprite(texture);

// Bucle principal
    while (window.isOpen())
    {
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // Cerrar la ventana si se recibe el evento de cerrar
                window.close();
            }
        }
    }
return 0;
}
