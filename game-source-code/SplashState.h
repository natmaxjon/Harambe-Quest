#ifndef SPLASH_STATE_H
#define SPLASH_STATE_H

#include <SFML/Graphics.hpp>

#include "State.h"
#include "GameLoop.h"

typedef unique_ptr<sf::Drawable> drawablePtr;

class SplashState: public State
{
public:
    
    /// Constructor
    /// @param game a shared pointer to a structure containing the game's state machine, asset manager, input manager and display window
    SplashState(gamePtr game);
    
    void initialise() override;
    void processInput() override;
    void update(float dt) override;
    void draw(float dt) override;   // dt not used... should State have an overloaded version with no parameters?
    
private:
    gamePtr game_;
    sf::Clock clock_;
    float progress_ = 0;
    
    sf::Sprite background_;
    sf::Text title_;
    sf::Text percentage_;
    sf::RectangleShape bar_;
    sf::RectangleShape barOutline_;
    vector<drawablePtr> drawables_;
    
    // Private helper functions
    void loadSounds(AssetManager& assetManager);
    void loadFonts(AssetManager& assetManager);
    void loadTextures(AssetManager& assetManager);

    void loadBackground(AssetManager& assetManager);
    void loadTitle(AssetManager& assetManager);
    void loadPercentage(AssetManager& assetManager);
    void loadProgressBar();

    
};

#endif
