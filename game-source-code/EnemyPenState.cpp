#include "EnemyPenState.h"
#include "Enemy.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

EnemyPenState::EnemyPenState(enemyPtr enemy, mazePtr maze) : enemy_{enemy}, maze_{maze} {}

void EnemyPenState::update(float dt)
{
    timeInState_ += dt;
    if (timeInState_ >= ENEMY_PEN_TIME)
    {
        enemy_->ScatterMode();
        enemy_->toggleInteractivity();
    }

    enemy_->animate(dt, "dead");
}

void EnemyPenState::enter()
{

}
