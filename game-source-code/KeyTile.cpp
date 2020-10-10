#include "KeyTile.h"

KeyTile::KeyTile(sf::Vector2f position, float angle, texturePtr texture, vector<tilePtr> gates):
    Tile(position, angle, texture),
    gates_{gates}
{
    // Error checking
}


void KeyTile::activate()
{
    notify(Observer::Event::KEY_EATEN);

    for (auto& gate : gates_)
        gate->remove();

    remove();
}
