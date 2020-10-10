#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include <SFML/Graphics.hpp>
#include <string>

#include "State.h"
#include "GameLoop.h"
#include "Button.h"
#include "Scoreboard.h"
#include "Soundboard.h"

class GameOverState: public State
{
public:
    GameOverState(gamePtr game, string mazeName, int lvlNumber);

    void initialise() override;
    void processInput() override;
    void update(float dt) override;
    void draw(float dt) override;

private:
    gamePtr game_;
    string mazeName_;
    int lvlNumber_;

    Button restartButton_;
    Button mainMenuButton_;
    Button highScoresButton_;

    Soundboard soundBoard_;

    sf::Text text_;
    sf::Text scoreText_;
    
    sf::Sprite coffinDancers_;
    float tStep_ = 936;
    float elapsedTime_ = 0;
    const int frameCount_ = 8;
    
    sf::Sprite sakuraTree_;
    sf::Sprite piaoPiao_;
    sf::Sprite petals_;
    float tStep1_ = 1200;
    const int frameCount1_ = 11;
    
    sf::Texture bgTexture_;
    sf::Sprite grass_;

    std::string nameEntered_ = "";
    sf::Text nameDisplay_;
    bool enterName_ = false;

    Scoreboard scoreBoard_ ;

    string songPlaying_;

    // Private helper functions
    void loadButtons(AssetManager& assetManager);
    void loadText(AssetManager& assetManager);
    void loadScoreText(AssetManager& assetManager);
    void loadScoreBoard(AssetManager& assetManager);
    void loadSprites(AssetManager& assetManager);
    
    void updateScores(AssetManager& assetManager);
    void updateNameEntered();
    bool isValid(uint32_t unicode);

};

#endif

