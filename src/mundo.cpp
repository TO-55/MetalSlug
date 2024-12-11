#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include "pikatanke.cpp"
#include "ventana.cpp"

int main()
{
    int fuerza = 5; // Incrementa este valor para mayor facilidad de desplazamiento
    int fuerzaSalto = 400; // Fuerza del impulso para el salto
    float ajusteAltura = 25.0f; // Ajuste de altura para alinear el sprite con el cuerpo dinamico

    // Crear una ventana
    Ventana ventana(800, 600, "Mi Ventana SFML");

    // Cargar la textura del sprite de fondo
    ventana.cargarTextura("assets/images/MSbackground.png");

    b2Vec2 vectorGravedad(0.0f, 10.0f);
    b2World mundo(vectorGravedad);

    // Crear el cuerpo dinamico usando la clase CuerpoDinamico
    CuerpoDinamico cuerpoBola(mundo, 400.0f, 200.0f - (25.0f * 2 + 10.0f), 25.0f, "assets/images/Pikachu_MS2.png");

    // Variables para la logica del juego
    bool enElSuelo = false;
    bool mirandoALaDerecha = true;

    // Bucle principal del juego
    while (ventana.estaAbierta())
    {
        // Procesar eventos de la ventana
        ventana.actualizar();

        // Controlar la bola con el teclado y actualizar el sprite
        cuerpoBola.controlarMovimiento(fuerza, fuerzaSalto, enElSuelo, mirandoALaDerecha, ajusteAltura);
        cuerpoBola.actualizarSprite(ajusteAltura);

        // Actualizar el mundo de Box2D
        mundo.Step(1.0f / 60.0f, 6, 2);

        // Limpiar la ventana y dibujar el fondo y el sprite
        ventana.dibujarFondo();
        ventana.dibujarSprite(cuerpoBola.obtenerSprite());
        
        // Mostrar todo en la ventana
        ventana.mostrar();

        // Mostrar la posicion de la bola en la consola
        std::cout << "Posicion de la bola: " << cuerpoBola.obtenerCuerpo()->GetPosition().x << ", " << cuerpoBola.obtenerCuerpo()->GetPosition().y << std::endl;
    }

    return 0;
}
