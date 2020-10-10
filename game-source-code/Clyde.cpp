#include "Clyde.h"
#include <cmath>
#include <iostream>

#include "EnemyScatterState.h"

Clyde::Clyde(map<string,texturePtr> textures, sf::Vector2f position, playerPtr player, mazePtr maze) :
         Enemy(textures, position, player, maze)
{
    current_dir_ = LEFT;
    default_dir_ = LEFT;
}

void Clyde::update(float dt)
{
    if (char_states_.empty())
        addCharState(std::make_shared<EnemyScatterState>(this, maze_));

    updateCharState();
    char_states_.top()->update(dt);
}

sf::Vector2f Clyde::getChaseTarget()
{
    auto target = sf::Vector2f{0,0};

    auto player_tile = player_->getCurrentTile();
    auto enemy_tile = getCurrentTile();

    float distance = sqrt((player_tile.x - enemy_tile.x)*(player_tile.x - enemy_tile.x)
            + (player_tile.y - enemy_tile.y)*(player_tile.y - enemy_tile.y));

    if (distance > 8*maze_->getTileLength())
       return player_tile;
    return getScatterTarget();
}


sf::Vector2f Clyde::getScatterTarget()
{
    auto bottomRight = get<1>(maze_->getMazeBounds());
    auto x = bottomRight.x - maze_->getTileLength()/2;
    auto y = bottomRight.y - maze_->getTileLength()/2;
    return sf::Vector2f{x,y};
}

