#include "EnemyScatterState.h"
#include "EnemyChaseState.h"
#include <iostream>

EnemyScatterState::EnemyScatterState(enemyPtr  enemy, mazePtr maze) : EnemyMovingState(enemy, maze) {}

void EnemyScatterState::update(float dt)
{
    timeInState_ += dt;

        if (timeInState_ >= SCATTER_MODE_TIMES[0])
        {
            enemy_->removeCharState();
            enemy_->ChaseMode();
            return;
        }

        enemy_->setFutureDir(findNextMove(enemy_->getScatterTarget()));
        moveEnemy(dt, enemy_->ScatterSpeed());

        enemy_->animate(dt, "default");
}

void EnemyScatterState::enter()
{
   if (!enemy_->isInteractive())
        enemy_->toggleInteractivity();

    enemy_->reverseDir();
}

