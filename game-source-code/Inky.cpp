#include "Inky.h"
#include <cmath>
#include <iostream>

#include "EnemyScatterState.h"

Inky::Inky(map<string,texturePtr> textures, sf::Vector2f position, playerPtr player, mazePtr maze, enemyPtr blinky) :
    Enemy(textures, position, player, maze), blinky_{blinky}
{
    current_dir_ = UP;
    default_dir_ = UP;
}


void Inky::update(float dt)
{
    if (char_states_.empty())
        addCharState(std::make_shared<EnemyScatterState>(this, maze_));

    updateCharState();
    char_states_.top()->update(dt);
}

sf::Vector2f Inky::getChaseTarget()
{
    auto target = player_->getCurrentTile() + float{2*maze_->getTileLength()}*player_->currentDir();

    target = float{2}*target - blinky_->getCurrentTile();

    return target;
}


sf::Vector2f Inky::getScatterTarget()
{
    auto topLeft = get<0>(maze_->getMazeBounds());
    auto x = topLeft.x + maze_->getTileLength()/2;
    auto y = topLeft.y + maze_->getHeight() - maze_->getTileLength()/2;
    return sf::Vector2f{x,y};
}




