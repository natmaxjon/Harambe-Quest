#include "Enemy.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include "EnemyScatterState.h"
#include "EnemyFrightenedState.h"
#include "EnemyChaseState.h"
#include "EnemyDeadState.h"
#include "EnemyPenState.h"
#include "EnemyFrozenState.h"

Enemy::Enemy(map<string,texturePtr> textures, sf::Vector2f position, playerPtr player, mazePtr maze):
    Character(textures, position, maze), player_{player}
{
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::onNotify(Event event)
{
    switch (event)
    {
        case Observer::Event::POWER_PELLET_EATEN:
            FrightenedMode();
            break;
        case Observer::Event::SUPER_PELLET_EATEN:
            // Flattened mode?
            break;
        default:
            break;
    }
}

void Enemy::animate(float dt, string textureKey)
{
    auto tStep = 300;
    int textureHeight = 32;
    int textureWidth = 32;

    animateTime+=dt;

   // cout << animateTime << endl;
    auto& currentTexture_ = stateTextures[textureKey];
    auto numFrames = static_cast<int>(currentTexture_->getSize().x/textureWidth);
    auto frame = static_cast<int>((animateTime/tStep) * numFrames) % numFrames;

    auto rowNum = 0;

    if (textureKey != "dead")
    {
        if (current_dir_ == DOWN)
            rowNum = 0;
        if (current_dir_ == LEFT)
            rowNum = 1;
        if (current_dir_ == RIGHT)
            rowNum = 2;
        if (current_dir_ == UP)
            rowNum = 3;
    }


    auto selectRect =  sf::IntRect(frame * textureWidth, rowNum*textureHeight, textureWidth, textureHeight);

    sprite_.setTexture(*currentTexture_);
    sprite_.setTextureRect(selectRect);

    sprite_.setOrigin(sf::Vector2f{static_cast<float>(textureWidth/2), static_cast<float>(textureHeight/2)});
    sprite_.setScale(1.6f,1.6f);
}

void Enemy::FrightenedMode()
{
    if (char_states_.size()>1)
        removeCharState();
    addCharState(std::make_unique<EnemyFrightenedState>(this, maze_));
    frightened_ = true;
}

bool Enemy::isFrightened()
{
    return frightened_;
}

void Enemy::DisableFrightenedMode()
{
    removeCharState();
    frightened_ = false;
}

void Enemy::ChaseMode()
{
    addCharState(std::make_unique<EnemyChaseState>(this, maze_));
}

void Enemy::ScatterMode()
{
    addCharState(std::make_unique<EnemyScatterState>(this, maze_));
}

void Enemy::reset()
{
    if (frightened_)
        DisableFrightenedMode();

    interactive_ = true;

    position_ = default_position_;
    char_states_ = {};
    addCharState(std::make_unique<EnemyScatterState>(this, maze_));
    current_dir_ = default_dir_;

}

void Enemy::PlayerDead()
{
    addCharState(std::make_unique<EnemyFrozenState>(this, maze_));
}

void Enemy::die()
{
    DisableFrightenedMode();
    addCharState(std::make_unique<EnemyDeadState>(this, maze_));
    notify(Observer::Event::GHOST_EATEN);
}

void Enemy::penState()
{
    addCharState(std::make_unique<EnemyPenState>(this, maze_));
}

sf::Vector2f Enemy::getPenPosition()
{
    return default_position_;
}

void Enemy::setFutureDir(sf::Vector2f dir)
{
    auto compass = vector<sf::Vector2f>{LEFT, RIGHT, UP, DOWN};
    if (find(compass.begin(), compass.end(), dir) != compass.end())
        future_dir_ = dir;
}

void Enemy::reverseDir()
{
    current_dir_ = float{-1}*current_dir_;
}

float Enemy::ScatterSpeed()
{
    float speed = SCATTER_MODE_SPEED*pow(1.1, lvlNumber_-1);

    if (speed > MAX_SPEED)
        return MAX_SPEED;

    return speed;
}

float Enemy::ChaseSpeed()
{
    float speed = CHASE_MODE_SPEED*pow(1.05, lvlNumber_-1);

    if (speed > MAX_SPEED)
        return MAX_SPEED;

    return speed;
}

float Enemy::FrightenedSpeed()
{
   float speed = FRIGHTENED_MODE_SPEED*pow(1.1, lvlNumber_-1);

    if (speed > MAX_SPEED)
        return MAX_SPEED;

    return speed;
}
