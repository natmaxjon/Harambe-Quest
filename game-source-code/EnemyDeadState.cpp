#include "EnemyDeadState.h"
#include "Enemy.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Vector2.hpp>

EnemyDeadState::EnemyDeadState(enemyPtr enemy, mazePtr maze) : EnemyMovingState(enemy, maze) {}

void EnemyDeadState::update(float dt)
{
    if (enemy_->getCurrentTile() == enemy_->getPenPosition())
    {
        enemy_->removeCharState();
        enemy_->penState();
        return;
    }

    enemy_->setFutureDir(findNextMove(enemy_->getPenPosition()));
    moveEnemy(dt, SCATTER_MODE_SPEED*3.5);

    enemy_->animate(dt, "frightened");
}

void EnemyDeadState::enter()
{
    if (enemy_->isInteractive())
        enemy_->toggleInteractivity();
}
