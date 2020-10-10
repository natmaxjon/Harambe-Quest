#include "Pinky.h"
#include <cmath>
#include <iostream>

#include "EnemyScatterState.h"

void Pinky::update(float dt)
{
    if (char_states_.empty())
        addCharState(std::make_shared<EnemyScatterState>(this, maze_));

    updateCharState();
    char_states_.top()->update(dt);
}

sf::Vector2f Pinky::getChaseTarget()
{
    auto target = player_->getCurrentTile() + float{4*maze_->getTileLength()}*player_->currentDir();
    return target;
}


sf::Vector2f Pinky::getScatterTarget()
{
    auto topLeft = get<0>(maze_->getMazeBounds());
    auto x = topLeft.x + maze_->getWidth() - maze_->getTileLength()/2;
    auto y = topLeft.y + maze_->getTileLength()/2;
    return sf::Vector2f{x,y};
}



