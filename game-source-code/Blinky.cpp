#include "Blinky.h"
#include <cmath>
#include <iostream>

#include "EnemyScatterState.h"

Blinky::Blinky(map<string,texturePtr> textures, sf::Vector2f position, playerPtr player, mazePtr maze) :
    Enemy(textures, position, player, maze)
{
    current_dir_ = RIGHT;
    default_dir_ = RIGHT;
}

void Blinky::update(float dt)
{
    if (char_states_.empty())
        addCharState(std::make_shared<EnemyScatterState>(this, maze_));

    updateCharState();
    char_states_.top()->update(dt);
}

sf::Vector2f Blinky::getChaseTarget()
{
    return player_->getCurrentTile();
}

sf::Vector2f Blinky::getScatterTarget()
{
    auto topLeft = get<0>(maze_->getMazeBounds());
    auto x = topLeft.x + maze_->getTileLength()/2;
    auto y = topLeft.y + maze_->getTileLength()/2;
    return sf::Vector2f{x,y};
}






