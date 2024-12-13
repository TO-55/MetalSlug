#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "pikatanke.cpp"
#include "ventana.cpp"
#include "suelo.cpp"
#include "camara.cpp"
#include "proyectil.cpp"
#include "meowth.cpp"

int main()
{
    int fuerza = 5000; // Incrementa este valor para mayor facilidad de desplazamiento
    long long int fuerzaSalto = 4000000; // Fuerza del impulso para el salto
    float ajusteAltura = 25.0f; // Ajuste de altura para alinear el sprite con el cuerpo dinamico

    // Crear una ventana con tamaño 600x275
    Ventana ventana(800, 275, "Mi Ventana SFML");

    // Cargar la textura del sprite de fondo
    ventana.cargarTextura("assets/images/MSbackground.png");

    b2Vec2 vectorGravedad(0.0f, 100.0f);
    b2World mundo(vectorGravedad);

    // Crear el cuerpo dinamico usando la clase CuerpoDinamico
    CuerpoDinamico cuerpoBola(mundo, 400.0f, 200.0f - (25.0f * 2 + 10.0f), 25.0f, "assets/images/Pikachu_MS2.png");

    // Crear el suelo usando la clase Suelo
    Suelo suelo(mundo, 0, 275.0f, 4300.0f, 10.0f);

    // Crear la camara usando la clase Camara con el sprite de fondo
    Camara camara(ventana.obtenerVentana(), 5.0f, ventana.obtenerFondo());

    // Crear a Meowth
    Personaje meowth("assets/images/MeowthMS.png", 400.f, 220.f, 500.f, 650.f, 0.2f, 0.2f);

    // Variables para la logica del juego
    bool enElSuelo = false;
    bool mirandoALaDerecha = true;

    // Límites de la ventana
    float limiteIzquierda = 0;
    float limiteDerecha = ventana.obtenerVentana().getSize().x;

    // Bucle principal del juego
    while (ventana.estaAbierta())
    {
        // Procesar eventos de la ventana
        ventana.actualizar();

        // Controlar la cámara con el teclado (si deseas mover la cámara manualmente)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            camara.moverIzquierda();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            camara.moverDerecha();
        }

        // Actualizar la vista de la ventana
        camara.actualizar();

        // Controlar la bola con el teclado y actualizar el sprite
        cuerpoBola.controlarMovimiento(fuerza, fuerzaSalto, enElSuelo, mirandoALaDerecha, ajusteAltura, limiteIzquierda, limiteDerecha);
        cuerpoBola.actualizarSprite(ajusteAltura);

        // Actualizar el mundo de Box2D
        mundo.Step(1.0f / 60.0f, 6, 2);

        cuerpoBola.actualizarProyectiles();

        meowth.actualizar();

        // Limpiar la ventana y dibujar el fondo y los sprites
        ventana.dibujarFondo();
        suelo.dibujar(ventana.obtenerVentana());
        ventana.dibujarSprite(cuerpoBola.obtenerSprite());
        cuerpoBola.dibujarProyectiles(ventana.obtenerVentana());
        meowth.dibujar(ventana.obtenerVentana());

        // Mostrar todo en la ventana
        ventana.mostrar();

        // Mostrar la posicion de la bola en la consola
        std::cout << "Posicion de la bola: " << cuerpoBola.obtenerCuerpo()->GetPosition().x << ", " << cuerpoBola.obtenerCuerpo()->GetPosition().y << std::endl;
    }

    return 0;
}
