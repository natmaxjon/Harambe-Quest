#include "EnemyMovingState.h"
#include "Enemy.h"
#include "GateTile.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iterator>
#include <cmath>
#include <list>

void EnemyMovingState::update(float dt)
{

}

void EnemyMovingState::enter()
{

}

void EnemyMovingState::moveEnemy(float dt, float speed)
{
    float distance = floor((speed*dt)/MIN_CHANGE)*MIN_CHANGE;

    auto current_block = enemy_->getCurrentTile();

    float distance_to_node = 0;

    auto position = enemy_->getSprite().getPosition();

    auto direction = enemy_->futureDir();

    if (enemy_->currentDir() == UP || enemy_->currentDir() == DOWN)
    {
        distance_to_node = enemy_->currentDir().y * current_block.y - enemy_->currentDir().y * position.y;
    } else
    {
        distance_to_node = enemy_->currentDir().x * current_block.x  - enemy_->currentDir().x * position.x;
    }

    auto topLeft = get<0>(maze_->getMazeBounds());
    auto bottomRight = get<1>(maze_->getMazeBounds());
    if ((current_block.x == topLeft.x+0.5f*maze_->getTileLength() && enemy_->currentDir()==LEFT)
        || (current_block.x == bottomRight.x-0.5f*maze_->getTileLength() &&  enemy_->currentDir()==RIGHT)
        || (current_block.y == topLeft.y+0.5f*maze_->getTileLength() &&  enemy_->currentDir()==UP)
        || (current_block.y == bottomRight.y-0.5f*maze_->getTileLength() &&  enemy_->currentDir()==DOWN))
    {
        auto moveDistance =  enemy_->currentDir()*(-1.f)*(maze_->getWidth()-maze_->getTileLength());
        enemy_->moveCharacter(moveDistance);
        return;
    }

    if ((distance_to_node>=0)&&(distance_to_node<distance))
    {
        enemy_->moveCharacter(enemy_->currentDir()*distance_to_node);

        enemy_->moveCharacter(enemy_->futureDir()*(distance-distance_to_node));

        enemy_->updateDir();

    } else
    {
        enemy_->moveCharacter(enemy_->currentDir()*distance);
    }
}

sf::Vector2f EnemyMovingState::findNextMove(sf::Vector2f target)
{

        GateTile::isNode(false);
        auto nodes = maze_->getNodes();
        auto distances = std::vector<double> {};

        auto valid_tiles = lookAround();

        for (sf::Vector2f d : valid_tiles)
        {
            distances.push_back(sqrt((target.x - d.x)*(target.x - d.x) + (target.y - d.y)*(target.y - d.y)));
        }

        auto id_min = std::distance(distances.begin(),std::min_element(distances.begin(),distances.end()));
        auto adj_tile = valid_tiles[id_min];

        auto dir = (adj_tile - enemy_->getCurrentTile())/float{maze_->getTileLength()};

        return dir;




}

std::vector<sf::Vector2f> EnemyMovingState::lookAround()
{
    GateTile::isNode(false);
    auto nodes = maze_->getNodes();
    auto compass = std::vector<sf::Vector2f>{UP,RIGHT,DOWN,LEFT};
    auto adj_tile = sf::Vector2f{0,0};
    auto valid_tiles = std::vector<sf::Vector2f>{};

    for (sf::Vector2f d : compass)
    {
        if (float{-1}*enemy_->currentDir() != d)
        {
            adj_tile = enemy_->getCurrentTile() + d*float{maze_->getTileLength()};

            if (std::find(nodes.begin(),nodes.end(),adj_tile) != nodes.end())
                valid_tiles.push_back(adj_tile);
        }
    }

    if (valid_tiles.empty())
    {
        valid_tiles.push_back(enemy_->getCurrentTile() + (enemy_->currentDir())*float{-1*maze_->getTileLength()});
  //      std::cout << "No valid tile" << std::endl;
    }


    return valid_tiles;
}
