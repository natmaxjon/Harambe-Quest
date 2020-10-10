#include "EnemyFrozenState.h"
#include "Enemy.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

EnemyFrozenState::EnemyFrozenState(enemyPtr enemy, mazePtr maze) : enemy_{enemy}, maze_{maze} {}

void EnemyFrozenState::update(float dt)
{
    timeInState_ += dt;
    if (timeInState_ >= DEATH_TIME)
    {
        enemy_->reset();
    }
}

void EnemyFrozenState::enter()
{
}
