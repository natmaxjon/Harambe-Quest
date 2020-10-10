#include "Button.h"
#include <iostream>

Button::Button(texturePtr texture, fontPtr font):
    texture_{texture},
    font_{font}
{
    sprite_.setTexture(*texture_);
    sprite_.setOrigin(sprite_.getGlobalBounds().width/2.f,
                      sprite_.getGlobalBounds().height/2.f);

    text_.setFont(*font_);
    text_.setString("TEXT");
    text_.setOrigin(text_.getGlobalBounds().width/2.f,
                    text_.getGlobalBounds().height/2.f);
    text_.setPosition(sprite_.getPosition());

    // Error checking
}

Button::Button(texturePtr texture):
    texture_{texture}
{
    sprite_.setTexture(*texture_);
    sprite_.setOrigin(sprite_.getGlobalBounds().width/2.f,
                      sprite_.getGlobalBounds().height/2.f);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite_);
    target.draw(text_);
    target.draw(outline_);
}

void Button::update(const sf::RenderWindow& window)
{
    if (isSelected_)
    {
        if (!isAlreadySelected_)
        {
            text_.setFillColor(textSelectedColour_);
            sprite_.setColor(spriteSelectedColour_);
            outline_.setOutlineColor(outlineSelectedColour_);
            isAlreadySelected_ = true;
        }
    }
    else if (!isSelected_)
    {
        if (isAlreadySelected_)
        {
        isAlreadySelected_ = false;
        }
        
        if (isHover(window))
        {
            if (!isAlreadyHover_)
            {
                text_.setFillColor(textHoverColour_);
                sprite_.setColor(spriteHoverColour_);
                outline_.setOutlineColor(outlineHoverColour_);
                isAlreadyHover_ = true;
            }
        }
        else if (!isHover(window))
        {
            if (isAlreadyHover_)
            {
                text_.setFillColor(textColour_);
                sprite_.setColor(spriteColour_);
                outline_.setOutlineColor(outlineColour_);
                isAlreadyHover_ = false;
            }
        }
    }
}

void Button::select() {isSelected_ = true;}
void Button::deselect() {isSelected_ = false;};

void Button::toggleSelection()
{
    if (isSelected_)
        isSelected_ = false;
    else
        isSelected_ = true;
}

bool Button::isHover(const sf::RenderWindow& window) const
{
    auto spriteBounds = sprite_.getGlobalBounds();

    if (spriteBounds.contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
        return true;

    return false;
}

void Button::setString(const string& text)
{
    text_ = sf::Text{};
    text_.setFont(*font_);
    text_.setString(text);
    text_.setOrigin(text_.getGlobalBounds().width/2.f,
                    text_.getGlobalBounds().height/2.f);
    text_.setScale(textScale_);
    text_.setFillColor(textColour_);
    text_.setRotation(angle_);

    // Error checking to ensure text fits within sprite
}

void Button::setOutline(float thickness)
{
    auto size = sprite_.getGlobalBounds();
    
    outline_ = sf::RectangleShape{sf::Vector2f{size.width,size.height}};
    outline_.setOrigin(outline_.getGlobalBounds().width/2.f,
                       outline_.getGlobalBounds().height/2.f);
    outline_.setOutlineThickness(thickness);
    outline_.setPosition(sprite_.getPosition());
    outline_.setFillColor(sf::Color::Transparent);
    outline_.setOutlineColor(outlineColour_);
}

void Button::setPosition(float x, float y)
{
    position_ = sf::Vector2f{x,y};
    sprite_.setPosition(x,y);
    text_.setPosition(x,y);
    outline_.setPosition(x,y);
}

void Button::setPosition(sf::Vector2f position)
{
    position_ = position;
    sprite_.setPosition(position);
    text_.setPosition(position);
    outline_.setPosition(position);
}

void Button::setSpriteScale(float factorX, float factorY)
{
    spriteScale_ = sf::Vector2f{factorX, factorY};
    sprite_.setScale(factorX, factorY);
}

void Button::setTextScale(float factorX, float factorY)
{
    textScale_ = sf::Vector2f{factorX, factorY};
    text_.setScale(factorX, factorY);
}

void Button::setRotation(float angle)
{
    angle_ = angle;
    sprite_.setRotation(angle);
    text_.setRotation(angle);
    outline_.setRotation(angle);
}

void Button::setColour(sf::Color colour)
{
    spriteColour_ = colour;
    textColour_ = colour;
    outlineColour_ = colour;
}

void Button::setHoverColour(sf::Color colour)
{
    spriteHoverColour_ = colour;
    textHoverColour_ = colour;
    outlineHoverColour_ = colour;
}

void Button::setSelectedColour(sf::Color colour)
{
    spriteSelectedColour_ = colour;
    textSelectedColour_ = colour;
    outlineSelectedColour_ = colour;
}

void Button::setSpriteColour(sf::Color normalColour, sf::Color hoverColour, sf::Color selectedColour)
{
    spriteColour_ = normalColour;
    spriteHoverColour_ = hoverColour;
    spriteSelectedColour_ = selectedColour;
}

void Button::setTextColour(sf::Color normalColour, sf::Color hoverColour, sf::Color selectedColour)
{
    textColour_ = normalColour;
    textHoverColour_ = hoverColour;
    textSelectedColour_ = selectedColour;
}

void Button::setOutlineColour(sf::Color normalColour, sf::Color hoverColour, sf::Color selectedColour)
{
    outlineColour_ = normalColour;
    outlineHoverColour_ = hoverColour;
    outlineSelectedColour_ = selectedColour;
}
