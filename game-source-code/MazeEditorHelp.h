#ifndef MAZE_EDITOR_HELP_H
#define MAZE_EDITOR_HELP_H

#include <SFML/Graphics.hpp>

#include "State.h"
#include "GameLoop.h"
#include "Button.h"

class MazeEditorHelp: public State
{
public:
    
    /// Constructor
    /// @param game a shared pointer to a structure containing the game's state machine, asset manager, input manager and display window
    MazeEditorHelp(gamePtr game);

    void initialise() override;
    void processInput() override;
    void update(float dt) override;
    void draw(float dt) override;

private:
    gamePtr game_;

    sf::Text title_;
    vector<vector<sf::Text>> pages_;
    sf::Text pageDisplay_;
        
    Button exitButton_;
    Button leftButton_;
    Button rightButton_;
    
    sf::Sprite bg;

    int pageNum_ = 0;
    
    // Private helper functions
    void loadTitle(AssetManager& assetManager);
    void loadText(AssetManager& assetManager);
    void loadButtons(AssetManager& assetManager);
    void loadPageProgress(AssetManager& assetManager);
        
    void nextPage();
    void previousPage();
};

#endif

