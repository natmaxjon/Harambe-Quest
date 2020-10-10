#include "Character.h"
#include <iostream>

/*------------- Static Members ---------------------*/
int Character::lvlNumber_ = 1;

void Character::setLevelNumber(const int& lvlNumber)
{
    lvlNumber_ = lvlNumber;
}
/*--------------------------------------------------*/

Character::Character(map<string,texturePtr> textures, sf::Vector2f position, mazePtr maze) :
stateTextures{textures}, position_{position}, default_position_{position}, maze_{maze}
{sprite_.setPosition(position_);};

sf::Sprite Character::getSprite()
{
    return sprite_;
}

sf::Vector2f Character::currentDir() const
{
    return current_dir_;
}

sf::Vector2f Character::futureDir() const
{
    return future_dir_;
}

void Character::updateDir()
{
    current_dir_ = future_dir_;
}

sf::Vector2f Character::getCurrentTile()
{
    return maze_->getTile(position_)->getPosition();
}

void Character::moveCharacter(const sf::Vector2f& delta)
{
    position_ += delta;
    sprite_.setPosition(position_);
}

void Character::addCharState(charStatePtr state)
{
    new_state_ = state;
    is_adding = true;
}

void Character::removeCharState()
{
    is_removing = true;
}

void Character::updateCharState()
{
    if (is_adding)
    {
        if (is_removing)
        {
            char_states_.pop();
            is_removing = false;
        }
        char_states_.push(new_state_);
        is_adding = false;
        char_states_.top()->enter();
    }

    if (is_removing)
    {
        char_states_.pop();
        is_removing = false;
        char_states_.top()->enter();
    }
}

void Character::toggleInteractivity()
{
    if (interactive_)
        interactive_ = false;
    else
        interactive_ = true;
}

bool Character::isInteractive() const
{
    return interactive_;
}

