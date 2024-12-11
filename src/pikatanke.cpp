#include "PikaTanke.hpp"

CuerpoDinamico::CuerpoDinamico(b2World& mundo, float posX, float posY, float radio, const std::string& texturaPath) {
    // Configurar el cuerpo dinámico
    b2BodyDef cuerpoDef;
    cuerpoDef.type = b2_dynamicBody;
    cuerpoDef.position.Set(posX, posY);
    cuerpo = mundo.CreateBody(&cuerpoDef);

    b2CircleShape forma;
    forma.m_radius = radio;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &forma;
    fixtureDef.density = 0.01f;
    fixtureDef.friction = 0.1f;
    cuerpo->CreateFixture(&fixtureDef);

    // Cargar la textura del sprite
    if (!textura.loadFromFile(texturaPath)) {
        std::cerr << "Error al cargar la textura" << std::endl;
        exit(-1);
    }

    // Crear el sprite y asignarle la textura
    sprite.setTexture(textura);
    sprite.setOrigin(textura.getSize().x / 2.0f, textura.getSize().y);
    sprite.setScale(0.3f, 0.3f);
}

void CuerpoDinamico::aplicarFuerza(float fuerzaX, float fuerzaY) {
    cuerpo->ApplyLinearImpulse(b2Vec2(fuerzaX, fuerzaY), cuerpo->GetWorldCenter(), true);
}

void CuerpoDinamico::actualizarSprite(float ajusteAltura) {
    sprite.setPosition(cuerpo->GetPosition().x, cuerpo->GetPosition().y + ajusteAltura);
}

sf::Sprite& CuerpoDinamico::obtenerSprite() {
    return sprite;
}

b2Body* CuerpoDinamico::obtenerCuerpo() {
    return cuerpo;
}

void CuerpoDinamico::controlarMovimiento(float fuerza, float fuerzaSalto, bool& enElSuelo, bool& mirandoALaDerecha, float ajusteAltura) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        aplicarFuerza(-fuerza, 0);
        if (mirandoALaDerecha) {
            sprite.setScale(-0.3f, 0.3f);
            mirandoALaDerecha = false;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        aplicarFuerza(fuerza, 0);
        if (!mirandoALaDerecha) {
            sprite.setScale(0.3f, 0.3f);
            mirandoALaDerecha = true;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && enElSuelo) {
        aplicarFuerza(0, -fuerzaSalto);
        enElSuelo = false; // Evitar saltos múltiples
    } else {
        // Detener la velocidad horizontal del cuerpo cuando no se presiona ninguna tecla de movimiento
        b2Vec2 velocidadActual = cuerpo->GetLinearVelocity();
        cuerpo->SetLinearVelocity(b2Vec2(0, velocidadActual.y));
    }

    // Verificar si el cuerpo está en el suelo
    enElSuelo = false;
    for (b2ContactEdge* ce = cuerpo->GetContactList(); ce; ce = ce->next) {
        b2Contact* c = ce->contact;
        if (c->IsTouching()) {
            enElSuelo = true;
            break;
        }
    }
}
