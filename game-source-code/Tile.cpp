#include "Tile.h"

Tile::Tile(sf::Vector2f position, float angle, texturePtr texture):
    position_{position},
    angle_{angle}
{
    sprite_.setTexture(*texture);
    sprite_.setOrigin(sprite_.getGlobalBounds().width/2.f,
                      sprite_.getGlobalBounds().height/2.f);
    sprite_.setPosition(position_.x, position_.y);
    sprite_.setRotation(angle_);
    
    // Error checking
}
