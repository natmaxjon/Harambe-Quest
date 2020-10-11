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

// Copied from https://github.com/SFML/SFML/wiki/Source%3A-Letterbox-effect-using-a-view
sf::View InputManager::getLetterboxView(sf::View view, int windowWidth, int windowHeight)
{
    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox effect.
    // A new view (with a new viewport set) is returned.

    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );

    return view;
}
