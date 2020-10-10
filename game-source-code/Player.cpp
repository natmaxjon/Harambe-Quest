#include "Player.h"
#include "DefaultCharacterState.h"
#include "PlayerSuperState.h"
#include "PlayerEatState.h"
#include "PlayerDeadState.h"
#include "Maze.h"

#include <string>
#include <cmath>
#include <iostream>

Player::Player(map<string,texturePtr> textures, sf::Vector2f position, mazePtr maze):
    Character(textures, position, maze),
    numLives(NUMBER_OF_LIVES)
{
    current_dir_ = RIGHT;
    future_dir_ = RIGHT;

}

Player::~Player()
{
    //dtor
}


void Player::update(float dt)
{

    if (char_states_.empty())
        addCharState(std::make_shared<DefaultCharacterState>(this, maze_));


    timeEating_ += dt;

    if (ghostsEaten_== 4 || timeEating_ > FRIGHTENED_MODE_TIME)
    {
        eatMode_ = false;
        ghostsEaten_ = 0;
        timeEating_ = 0;
    }

    updateCharState();
    char_states_.top()->update(dt);

}

void Player::animate(float dt, string textureKey)
{
    auto tStep = 270;
    int textureHeight = 40;
    int textureWidth = 40;

    if (textureKey == "dead")
        textureWidth = 55;

    if (isInteractive() && eatMode_)
        textureKey = "kill " + textureKey;

    animateTime+=dt;

    auto& currentTexture_ = stateTextures[textureKey];
    auto numFrames = static_cast<int>(currentTexture_->getSize().x/textureWidth);
    auto frame = static_cast<int>((animateTime/tStep) * numFrames) % numFrames;

    auto selectRect =  sf::IntRect(frame * textureWidth, 0, textureWidth, textureHeight);

    sprite_.setTexture(*currentTexture_);
    sprite_.setTextureRect(selectRect);

    sprite_.setOrigin(sf::Vector2f{static_cast<float>(textureWidth/2), static_cast<float>(textureHeight/2)});

    if (super_mode)
        sprite_.setScale(1.8,1.8);
    else
        sprite_.setScale(1.25,1.25);
}

void Player::onNotify(Event event)
{
    switch (event)
    {
        case Observer::Event::POWER_PELLET_EATEN:
            eatMode_ = true;
            ghostsEaten_ = 0;
            timeEating_ = 0;
            break;
        case Observer::Event::SUPER_PELLET_EATEN:
            enableSuperMode();
            break;
        case Observer::Event::GHOST_EATEN:
            ghostsEaten_++;
            break;
        default:
            break;
    }
}

void Player::enableSuperMode()
{
    super_mode = true;
    addCharState(std::make_shared<PlayerSuperState>(this, maze_));
}

void Player::disableSuperMode()
{
    super_mode = false;
    removeCharState();
}

bool Player::isSuper()
{
    return super_mode;
}

void Player::Up()
{
    future_dir_ = UP;
}

void Player::Down()
{
    future_dir_ = DOWN;
}

void Player::Right()
{
    future_dir_ = RIGHT;
}

void Player::Left()
{
    future_dir_ = LEFT;
}

void Player::reset()
{
    char_states_ = {};
    addCharState(std::make_shared<DefaultCharacterState>(this, maze_));
    current_dir_ = RIGHT;
    future_dir_ = RIGHT;
    position_ = default_position_;
    eatMode_ = false;
    super_mode = false;
    interactive_ = true;
}

void Player::eat()
{
    addCharState(std::make_shared<PlayerEatState>(this, maze_));
}

void Player::die()
{
    addCharState(std::make_shared<PlayerDeadState>(this, maze_));
    numLives = numLives - 1;
    notify(Observer::Event::LIFE_LOST);
}

int Player::livesLeft()
{
    return numLives;
}

float Player::SuperSpeed()
{
   float speed = SUPER_MODE_SPEED*pow(PLAYER_SPEED_INCREASE, lvlNumber_-1);

    if (speed > MAX_SPEED)
        return MAX_SPEED;

    return speed;
}


float Player::NormalSpeed()
{
   float speed = NORMAL_CHARACTER_SPEED*pow(PLAYER_SPEED_INCREASE, lvlNumber_-1);

    if (speed > MAX_SPEED)
        return MAX_SPEED;

    return speed;
}


