#include "PlayerSuperState.h"
#include <iostream>
#include "GateTile.h"

void PlayerSuperState::update(float dt)
{
    timeInState_ += dt;
    GateTile::isNode(true);

    if (timeInState_ >= SUPER_MODE_TIME)
    {
        GateTile::isNode(false);
        player_->disableSuperMode();
    }

    movePlayer(dt, player_->SuperSpeed(), player_, maze_);

    player_->animate(dt, getTextureName());
}

void PlayerSuperState::enter()
{
}

string PlayerSuperState::getTextureName()
{
    if (player_->currentDir() == RIGHT)
        return "super right";
    if (player_->currentDir() == LEFT)
        return "super left";
    if (player_->currentDir() == UP)
        return "super up";
    if (player_->currentDir() == DOWN)
        return "super down";
    
    return "super right";
}
