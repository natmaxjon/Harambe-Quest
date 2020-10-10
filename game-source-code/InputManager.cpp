#include "InputManager.h"

bool InputManager::isObjectClicked(sf::Sprite object, sf::Mouse::Button mouseButton, const sf::RenderWindow& window) const
{
    if(!sf::Mouse::isButtonPressed(mouseButton))
        return false;
    
    sf::FloatRect spriteBounds(object.getPosition().x,
                               object.getPosition().y,
                               object.getGlobalBounds().width,
                               object.getGlobalBounds().height);
    
    if (spriteBounds.contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
        return true;
    
    return false;
}

sf::Vector2f InputManager::getMousePosition(sf::RenderWindow window) const
{
    return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

bool InputManager::isExitRequest(sf::Event event) const
{
    auto case1 = (event.type == sf::Event::Closed);
    auto case2 = (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape);

    if (case1 || case2)
        return true;
    
    return false;
}
