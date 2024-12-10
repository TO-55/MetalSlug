#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>

int main()
{
    int fuerza = 5; // Incrementa este valor para mayor facilidad de desplazamiento
    int fuerzaSalto = 400; // Fuerza del impulso para el salto
    float ajusteAltura = 25.0f; // Ajuste de altura para alinear el sprite con el cuerpo dinámico

    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Ejemplo de Física con Box2D y SFML");

    b2Vec2 vectorGravedad(0.0f, 10.0f);
    b2World mundo(vectorGravedad);

    // Crear un suelo estático
    b2BodyDef cuerpoSueloDef;
    cuerpoSueloDef.position.Set(400, 500.0f); // Posición del centro del suelo
    b2Body* cuerpoSuelo = mundo.CreateBody(&cuerpoSueloDef);

    b2PolygonShape formaSuelo;
    int boxWidth = 600; // 600 pixeles de ancho
    int boxHeight = 10; // 10 pixeles de alto
    formaSuelo.SetAsBox(boxWidth / 2.0f, boxHeight / 2.0f);

    b2FixtureDef fixtureSueloDef;
    fixtureSueloDef.shape = &formaSuelo;
    fixtureSueloDef.friction = 1.0f;
    cuerpoSuelo->CreateFixture(&fixtureSueloDef);

    // Crear un cuerpo dinámico
    b2BodyDef cuerpoBolaDef;
    cuerpoBolaDef.type = b2_dynamicBody;
    float yPosicionBola = 500.0f - (25.0f * 2 + boxHeight); // Ajustar posición y
    cuerpoBolaDef.position.Set(400.0f, yPosicionBola);
    b2Body* cuerpoBola = mundo.CreateBody(&cuerpoBolaDef);

    b2CircleShape formaBola;
    formaBola.m_radius = 25.0f;

    b2FixtureDef fixtureBolaDef;
    fixtureBolaDef.shape = &formaBola;
    fixtureBolaDef.density = 0.01f;
    fixtureBolaDef.friction = 0.1f; // Reduce la fricción para facilitar el movimiento
    cuerpoBola->CreateFixture(&fixtureBolaDef);

    // Cargar la textura del sprite
    sf::Texture texturaBola;
    if (!texturaBola.loadFromFile("assets/images/Pikachu_MS2.png")) {
        return -1; // Manejar error en caso de que la textura no se cargue correctamente
    }

    // Crear el sprite y asignarle la textura
    sf::Sprite spriteBola(texturaBola);
    spriteBola.setOrigin(texturaBola.getSize().x / 2.0f, texturaBola.getSize().y);
    spriteBola.setScale(.3, .3);

    // Variable para verificar si el cuerpo está en el suelo
    bool enElSuelo = false;

    // Variable para llevar el seguimiento de la dirección del sprite
    bool mirandoALaDerecha = true;

    // Bucle principal del juego
    while (ventana.isOpen())
    {
        // Procesar eventos
        sf::Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
                ventana.close();
        }

        // Controlar la bola con el teclado
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            cuerpoBola->ApplyLinearImpulse(b2Vec2(-fuerza, 0), cuerpoBola->GetWorldCenter(), true);
            if (mirandoALaDerecha) {
                spriteBola.setScale(-.3, .3); // Voltear el sprite hacia la izquierda
                mirandoALaDerecha = false;
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            cuerpoBola->ApplyLinearImpulse(b2Vec2(fuerza, 0), cuerpoBola->GetWorldCenter(), true);
            if (!mirandoALaDerecha) {
                spriteBola.setScale(.3, .3); // Voltear el sprite hacia la derecha
                mirandoALaDerecha = true;
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && enElSuelo) {
            cuerpoBola->ApplyLinearImpulse(b2Vec2(0, -fuerzaSalto), cuerpoBola->GetWorldCenter(), true);
            enElSuelo = false; // Evitar saltos múltiples
        } else {
            // Detener la velocidad horizontal del cuerpo cuando no se presiona ninguna tecla de movimiento
            b2Vec2 velocidadActual = cuerpoBola->GetLinearVelocity();
            cuerpoBola->SetLinearVelocity(b2Vec2(0, velocidadActual.y));
        }

        // Verificar si el cuerpo está en el suelo
        enElSuelo = false;
        for (b2ContactEdge* ce = cuerpoBola->GetContactList(); ce; ce = ce->next)
        {
            b2Contact* c = ce->contact;
            if (c->IsTouching())
            {
                enElSuelo = true;
                break;
            }
        }

        // Actualizar el mundo de Box2D
        mundo.Step(1.0f / 60.0f, 6, 2);
        std::cout << "Posición de la bola: " << cuerpoBola->GetPosition().x << ", " << cuerpoBola->GetPosition().y << std::endl;

        // Actualizar la posición y rotación del sprite para que coincida con el cuerpo físico
        spriteBola.setPosition(cuerpoBola->GetPosition().x, cuerpoBola->GetPosition().y + ajusteAltura);

        // Limpiar la ventana
        ventana.clear();

        // Dibujar el suelo
        sf::RectangleShape suelo(sf::Vector2f(boxWidth, boxHeight));
        suelo.setOrigin(boxWidth / 2.0f, boxHeight / 2.0f); // El origen x,y está en el centro de la forma
        suelo.setPosition(cuerpoSuelo->GetPosition().x, cuerpoSuelo->GetPosition().y);
        ventana.draw(suelo);

        // Dibujar el sprite de la bola
        ventana.draw(spriteBola);

        // Mostrar la ventana
        ventana.display();
    }

    return 0;
}
