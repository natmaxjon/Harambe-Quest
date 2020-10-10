#include "GateTile.h"

GateTile::GateTile(sf::Vector2f position, float angle, texturePtr normalTexture, texturePtr brokenTexture):
    Tile{position, angle, normalTexture}
{
    brokenSprite_.setTexture(*brokenTexture);
    brokenSprite_.setOrigin(brokenSprite_.getGlobalBounds().width/2.f,
                            brokenSprite_.getGlobalBounds().height/2.f);
    brokenSprite_.setPosition(position.x, position.y);
    brokenSprite_.setRotation(angle);
}

void GateTile::activate()
{
    if (!isBroken_)
    {
        notify(Observer::Event::GATE_BROKEN);
        isBroken_ = true;
        setSprite(brokenSprite_);
    }
}

bool GateTile::isNode()
{
    if (isBroken_)
        return true;

    return isNode_;
}

bool GateTile::isNode_ = false;
