#include "EnemyFrightenedState.h"
#include <iostream>

EnemyFrightenedState::EnemyFrightenedState(enemyPtr enemy, mazePtr maze) : EnemyMovingState(enemy, maze){}

void EnemyFrightenedState::update(float dt)
{
    timeInState_ += dt;

        if (timeInState_ >= FRIGHTENED_MODE_TIME)
        {
            enemy_->DisableFrightenedMode();
        }

    enemy_->setFutureDir(findRandomMove());
    moveEnemy(dt, enemy_->FrightenedSpeed());

    enemy_->animate(dt, "frightened");
}

void EnemyFrightenedState::enter()
{
    if (!enemy_->isInteractive())
        enemy_->toggleInteractivity();
}


sf::Vector2f EnemyFrightenedState::findRandomMove()
{
    auto valid_tiles = lookAround();

    auto adj_tile = valid_tiles.at(rand()%valid_tiles.size());

    return (adj_tile - enemy_->getCurrentTile())/float{TILE_LENGTH};
}


