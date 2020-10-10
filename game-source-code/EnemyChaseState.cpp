#include "EnemyChaseState.h"
#include <iostream>

EnemyChaseState::EnemyChaseState(enemyPtr enemy, mazePtr maze) : EnemyMovingState(enemy, maze) {}

void EnemyChaseState::update(float dt)
{
    timeInState_ += dt;
        if (timeInState_ >= CHASE_MODE_TIMES[0])
        {
            enemy_->ScatterMode();
            return;
        }

    enemy_->setFutureDir(findNextMove(enemy_->getChaseTarget()));
    moveEnemy(dt, enemy_->ChaseSpeed());

    enemy_->animate(dt, "default");
}

void EnemyChaseState::enter()
{
    enemy_->reverseDir();
    if (!enemy_->isInteractive())
        enemy_->toggleInteractivity();
}

