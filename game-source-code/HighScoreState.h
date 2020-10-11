#ifndef HIGH_SCORE_STATE_H
#define HIGH_SCORE_STATE_H

#include <SFML/Graphics.hpp>

#include "State.h"
#include "GameLoop.h"
#include "Button.h"

class HighScoreState: public State
{
public:

    /// Constructor
    /// @param game a shared pointer to a structure containing the game's state machine, asset manager, input manager and display window
    HighScoreState(gamePtr game);

    void initialise() override;
    void processInput() override;
    void update(float dt) override;
    void draw(float dt) override;

private:
    gamePtr game_;

    Button exitButton_;
    Button rightButton_;
    Button leftButton_;

    vector<string> mazeNames_;
    string currentMaze_;
    vector<string>::iterator mazeIt;

    sf::Sprite background;

    float timeFlash = 0;


    sf::Text mazeDisplay_;
    vector<sf::Text> entries;
    sf::Text title_;
    // Private helper functions
    void loadButtons(AssetManager& assetManager);
    void loadMazes(AssetManager& assetManager);
    void loadHighScores(AssetManager& assetManager);
    void loadTitle(AssetManager& assetManager);
    void previousMaze();
    void nextMaze();
    void checkMusic();

    sf::Color Gold = sf::Color(212,175,55);
    sf::Color Silver = sf::Color(192,192,192);
    sf::Color Bronze = sf::Color(205,127,50);


};

#endif

