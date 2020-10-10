#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SFML/Graphics.hpp>

using namespace std;

class InputManager
{
public:
    InputManager() {}
    ~InputManager() {}
    
    // Hmmm... this will probably have to change
    bool isObjectClicked(sf::Sprite object, sf::Mouse::Button mouseButton, const sf::RenderWindow& window) const;
    
    sf::Vector2f getMousePosition(sf::RenderWindow window) const;
    
    bool isExitRequest(sf::Event event) const;
    
    // Implement input functions that would be useful for handling input independent of state below

    
private:

};

#endif
