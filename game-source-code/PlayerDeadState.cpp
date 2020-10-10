#include "PlayerDeadState.h"
#include "Player.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

PlayerDeadState::PlayerDeadState(playerPtr player, mazePtr maze) : player_{player}, maze_{maze} {}

void PlayerDeadState::update(float dt)
{
    timeInState_ += dt;
    if (timeInState_ >= DEATH_TIME)
    {
        player_->reset();
    }

    string textureName = "dead";

    player_->animate(dt, textureName);
}

void PlayerDeadState::enter()
{
    if (player_->isInteractive())
        player_->toggleInteractivity();
}
