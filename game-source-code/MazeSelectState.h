#ifndef MAZE_SELECT_STATE_H
#define MAZE_SELECT_STATE_H

#include <SFML/Graphics.hpp>

#include "State.h"
#include "GameLoop.h"
#include "Button.h"

class MazeSelectState: public State
{
public:
    
    /// Constructor
    /// @param game a shared pointer to a structure containing the game's state machine, asset manager, input manager and display window
    MazeSelectState(gamePtr game);

    void initialise() override;
    void processInput() override;
    void update(float dt) override;
    void draw(float dt) override;

private:
    gamePtr game_;
    
    sf::Vector2f topLeft_{106.f, 114.f};
    float tileLength_ = 28.f;

    Button exitButton_;
    Button rightButton_;
    Button leftButton_;
    Button playButton_;
    Button deleteButton_;

    sf::Texture bgTexture_;
    sf::Sprite background_;
    vector<sf::Sprite> characters_;

    vector<string> mazeNames_;
    string currentMaze_;
    vector<string>::iterator mazeIt;

    sf::Text mazeDisplayName_;
    sf::Text title_;
    
    vector<string> layout_;
    vector<string> rotationMap_;
    vector<sf::Vector2f> startPos_;

    // Private helper functions
    void loadButtons(AssetManager& assetManager);
    void loadMazes(AssetManager& assetManager);
    void loadMazeData(AssetManager& assetManager);
    void loadCharacters(AssetManager& assetManager);

    void drawMaze();
    sf::Sprite char2Sprite(char c);
    float char2Angle(char c);
    
    void loadTitle(AssetManager& assetManager);
    void previousMaze();
    void nextMaze();
    void deleteMaze();

};

#endif


