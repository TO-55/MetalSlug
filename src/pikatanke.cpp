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

void CuerpoDinamico::disparar(ProjectileType tipo) {
    if(frameSinceLastShot >= framesPerShot) {
        // Get the character's current position
        float posX = cuerpo->GetPosition().x;
        float posY = cuerpo->GetPosition().y;

        // Adjust projectile spawn position
        float offsetY = 30.0f;
        float offsetX = 20.0f;
        posY = posY - offsetY;
        posX += mirandoALaDerecha ? offsetX : -offsetX;

        // Create the projectile
        Projectile proyectil;
        proyectil.shape.setRadius(5.f);
        proyectil.shape.setOrigin(5.f, 5.f);
        proyectil.shape.setPosition(posX, posY);
        proyectil.type = tipo;

        // Set projectile properties based on type
        switch(tipo) {
            case NORMAL:
                proyectil.velocity = sf::Vector2f(mirandoALaDerecha ? 15.0f : -15.0f, 0.0f);
                proyectil.damage = 10.0f;
                proyectil.shape.setFillColor(sf::Color::Yellow);
                break;
            case EXPLOSIVE:
                proyectil.velocity = sf::Vector2f(mirandoALaDerecha ? 10.0f : -10.0f, 0.0f);
                proyectil.damage = 25.0f;
                proyectil.shape.setFillColor(sf::Color::Red);
                break;
            case RAPID:
                proyectil.velocity = sf::Vector2f(mirandoALaDerecha ? 25.0f : -25.0f, 0.0f);
                proyectil.damage = 5.0f;
                proyectil.shape.setFillColor(sf::Color::Blue);
                break;
        }

        // Store projectile
        proyectiles.push_back(proyectil);
        
        frameSinceLastShot = 0;
    }
}

void CuerpoDinamico::actualizarProyectiles() {
    frameSinceLastShot++;
    
    for (size_t i = 0; i < proyectiles.size();) {
        // Move projectile
        proyectiles[i].shape.move(proyectiles[i].velocity);
        sf::Vector2f pos = proyectiles[i].shape.getPosition();

        // Special effects for explosive projectiles
        if (proyectiles[i].type == EXPLOSIVE) {
            // Add particle effect or explosion animation here
        }

        // Remove projectiles that are off screen
        if (pos.x < 0 || pos.x > 800) {
            proyectiles.erase(proyectiles.begin() + i);
        } else {
            i++;
        }
    }
}

void CuerpoDinamico::dibujarProyectiles(sf::RenderWindow& ventana) {
    for (const auto& proyectil : proyectiles) {
        ventana.draw(proyectil.shape);
    }
}

void CuerpoDinamico::checkProjectileCollisions(sf::FloatRect targetBounds) {
    for (size_t i = 0; i < proyectiles.size();) {
        if (proyectiles[i].shape.getGlobalBounds().intersects(targetBounds)) {
            // Handle collision based on projectile type
            switch(proyectiles[i].type) {
                case EXPLOSIVE:
                    // Add explosion effect here
                    std::cout << "Explosive hit! Damage: " << proyectiles[i].damage << std::endl;
                    break;
                case RAPID:
                    std::cout << "Rapid hit! Damage: " << proyectiles[i].damage << std::endl;
                    break;
                case NORMAL:
                default:
                    std::cout << "Normal hit! Damage: " << proyectiles[i].damage << std::endl;
                    break;
            }
            
            // Remove the projectile after collision
            proyectiles.erase(proyectiles.begin() + i);
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
        disparar(NORMAL);
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