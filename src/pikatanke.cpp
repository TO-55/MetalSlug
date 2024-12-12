#include "PikaTanke.hpp"

CuerpoDinamico::CuerpoDinamico(b2World& mundo, float posX, float posY, float radio, const std::string& texturaPath) {
    // Configurar el cuerpo dinamico
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
    sprite.setOrigin(textura.getSize().x / 2.0f, textura.getSize().y); // Ajustar el origen para alinearlo al suelo
    sprite.setScale(0.2f, 0.2f); // Establecer la escala del sprite a (0.2, 0.2)
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

void CuerpoDinamico::dibujarProyectiles(sf::RenderWindow& ventana){
    for (auto& proyectil : proyectiles) {
        ventana.draw(proyectil);
    }
}

void CuerpoDinamico::disparar() {
    if(relojDisparo.getElapsedTime().asSeconds() >= tiempoEntreDisparos){
    // Get the character's current position
    float posX = sprite.getPosition().x;
    float posY = sprite.getPosition().y;
    
    // Create the projectile
    sf::CircleShape proyectil(5.f);
    proyectil.setFillColor(sf::Color::Yellow);
    proyectil.setOrigin(5.f,5.f);
    proyectil.setPosition(posX,posY);

    //set the projectile velocity
    float velocidadProyectil = 10.f;
    sf::Vector2f veloidad(mirandoALaDerecha ? velocidadProyectil : -velocidadProyectil, 0.f);

    //Store projectiles and velocity
    proyectiles.push_back(proyectil);
    velocidadesProyectiles.push_back(veloidad);
    
    //Reset Cooldown
    relojDisparo.restart();
    }
}

void CuerpoDinamico::actualizarProyectiles() {
    for (size_t i = 0; i < proyectiles.size();) {
        proyectiles[i].move(velocidadesProyectiles[i]);
        sf::Vector2f pos = proyectiles[i].getPosition();

        if (pos.x < 0 || pos.x > 800 || pos.y < 0 || pos.y > 600) {
            proyectiles.erase(proyectiles.begin() + i);
            velocidadesProyectiles.erase(velocidadesProyectiles.begin() + i);
        } else {
            i++;
        }
    }
}


void CuerpoDinamico::controlarMovimiento(float fuerza, float fuerzaSalto, bool& enElSuelo, bool& mirandoALaDerecha, float ajusteAltura, float limiteIzquierda, float limiteDerecha) {
    float escala = 1.0f; // Define la escala adecuada según tu configuración
    bool moviendose = false; // Variable para verificar si el personaje se está moviendo

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        aplicarFuerza(-fuerza, 0);
        moviendose = true;
        if (mirandoALaDerecha) {
            sprite.setScale(-0.2f, 0.2f); // Asegurarse de que la escala se ajusta correctamente al cambiar de dirección
            mirandoALaDerecha = false;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        aplicarFuerza(fuerza, 0);
        moviendose = true;
        if (!mirandoALaDerecha) {
            sprite.setScale(0.2f, 0.2f); // Asegurarse de que la escala se ajusta correctamente al cambiar de dirección
            mirandoALaDerecha = true;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && enElSuelo) {
        aplicarFuerza(0, -fuerzaSalto);
        enElSuelo = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        disparar();
    }

    // Detener la velocidad horizontal del cuerpo cuando no se presiona ninguna tecla de movimiento
    if (!moviendose) {
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
