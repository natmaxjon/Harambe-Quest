#include "DefaultCharacterState.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

void DefaultCharacterState::update(float dt)
{
    movePlayer(dt, player_->NormalSpeed(), player_, maze_);

    player_->animate(dt, getTextureName());
}

void DefaultCharacterState::enter()
{
   // player_->setDefaultTexture();
}

string DefaultCharacterState::getTextureName()
{
    if (player_->currentDir() == RIGHT)
        return "right";
    if (player_->currentDir() == LEFT)
        return "left";
    if (player_->currentDir() == UP)
        return "up";
    if (player_->currentDir() == DOWN)
        return "down";
    
    return "right";
}
