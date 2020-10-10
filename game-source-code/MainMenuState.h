#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include <SFML/Graphics.hpp>

#include "State.h"
#include "GameLoop.h"
#include "Button.h"

class MainMenuState: public State
{
public:
    
    /// Constructor
    /// @param game a shared pointer to a structure containing the game's state machine, asset manager, input manager and display window
    MainMenuState(gamePtr game);

    void initialise() override;
    void processInput() override;
    void update(float dt) override;
    void draw(float dt) override;

private:
    gamePtr game_;

    sf::Text title_;
    Button playButton_;
    Button levelEditorButton_;
    Button highScoresButton_;
    Button how2PlayButton_;
    Button creditsButton_;
    
    sf::Sprite bg;

    // Private helper functions
    void loadTitle(AssetManager& assetManager);
    void loadButtons(AssetManager& assetManager);

};

#endif

