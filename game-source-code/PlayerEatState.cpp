#include "PlayerEatState.h"
#include "Player.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

PlayerEatState::PlayerEatState(playerPtr player, mazePtr maze) : player_{player}, maze_{maze} {}

void PlayerEatState::update(float dt)
{
    timeInState_ += dt;
    if (timeInState_ >= EATING_TIME)
    {
        player_->toggleInteractivity();
        player_->removeCharState();
    }

    string textureName;
    if (player_->currentDir() == RIGHT)
    {
        if (player_->isSuper())
            textureName = "hit super right";
        else
            textureName = "hit right";
    }

    if (player_->currentDir() == LEFT)
    {
        if (player_->isSuper())
            textureName = "hit super left";
        else
            textureName = "hit left";
    }

    if (player_->currentDir() == UP)
    {
        if (player_->isSuper())
            textureName = "hit super up";
        else
            textureName = "hit up";
    }

    if (player_->currentDir() == DOWN)
    {
        if (player_->isSuper())
            textureName = "hit super down";
        else
            textureName = "hit down";
    }

    player_->animate(dt, textureName);
}

void PlayerEatState::enter()
{
    if (player_->isInteractive())
        player_->toggleInteractivity();
}
