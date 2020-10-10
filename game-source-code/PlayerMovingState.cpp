#include "PlayerMovingState.h"
#include "Player.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

void PlayerMovingState::movePlayer(float dt, float speed, playerPtr  player_, mazePtr maze_)
{
    float distance = floor((speed*dt)/MIN_CHANGE)*MIN_CHANGE;


    if (player_->currentDir() == float{-1}*player_->futureDir())
    {
        player_->updateDir();
    }

    auto nodes = maze_->getNodes();

    auto position = player_->getSprite().getPosition();

    auto current_block = player_->getCurrentTile();

    auto destination_block = sf::Vector2f {current_block.x + player_->futureDir().x*maze_->getTileLength(),
                                           current_block.y + player_->futureDir().y*maze_->getTileLength()};


    auto distance_to_node = 0.0f;

    if (player_->currentDir().x == 0)
    {
        distance_to_node = player_->currentDir().y * current_block.y - player_->currentDir().y *  position.y;
    } else
    {
        distance_to_node = player_->currentDir().x * current_block.x  - player_->currentDir().x *  position.x;
    }

    auto topLeft = get<0>(maze_->getMazeBounds());
    auto bottomRight = get<1>(maze_->getMazeBounds());
    auto mazeSize = bottomRight - topLeft;

    if ((current_block.x == topLeft.x+0.5f*maze_->getTileLength() && player_->currentDir()==LEFT)
        || (current_block.x == bottomRight.x-0.5f*maze_->getTileLength() && player_->currentDir()==RIGHT)
        || (current_block.y == topLeft.y+0.5f*maze_->getTileLength() && player_->currentDir()==UP)
        || (current_block.y == bottomRight.y-0.5f*maze_->getTileLength() && player_->currentDir()==DOWN))
    {

        auto moveDistance = sf::Vector2f{};

        if (player_->currentDir().x == 0.f)
            moveDistance = player_->currentDir()*(-1.f)*(maze_->getHeight()-maze_->getTileLength());
        else
            moveDistance = player_->currentDir()*(-1.f)*(maze_->getWidth()-maze_->getTileLength());

        auto isValidNode = maze_->getTile(position + moveDistance)->isNode();

        if (isValidNode)
        {
            player_->moveCharacter(moveDistance);
            return;
        }
    }


    if (!maze_->getTile(destination_block)->isNode() && (distance_to_node>=0)&&(distance_to_node<distance))
    {
        if (player_->currentDir() != float{-1}*player_->futureDir())
        {
            if (maze_->getTile(current_block + player_->currentDir()*maze_->getTileLength())->isNode())
            {
                 player_->moveCharacter(player_->currentDir()*distance);
                 return;
            }

        return;
        }

    player_->moveCharacter(player_->currentDir()*distance_to_node);
    return;

    }

    if ((distance_to_node>=0)&&(distance_to_node<distance))
    {
         player_->moveCharacter(player_->currentDir()*distance_to_node);

         player_->moveCharacter(player_->futureDir()*(distance-distance_to_node));

         player_->updateDir();
    return;

    }

    player_->moveCharacter(player_->currentDir()*distance);

}
