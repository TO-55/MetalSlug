#include "Target.hpp"

bool Target::isAlive() const {
    return alive;
}

sf::FloatRect Target::getBounds() const {
    // Return the bounding box of your target
    return sf::FloatRect(); // Replace with actual implementation
}

void Target::takeDamage() {
    alive = false;
}
