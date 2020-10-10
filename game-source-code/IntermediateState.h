#ifndef INTERMEDIATE_STATE_H
#define INTERMEDIATE_STATE_H

#include <SFML/Graphics.hpp>

#include "State.h"
#include "GameLoop.h"
#include "Button.h"

class IntermediateState: public State
{
public:
    IntermediateState(gamePtr game, string mazeName = "Classic", int lvlNumber = 1);

    void initialise() override;
    void processInput() override;
    void update(float dt) override;
    void draw(float dt) override;

private:
    gamePtr game_;
    float elapsedTime = 0;
    string mazeName_;
    int lvlNumber_;

    vector<sf::Text> lines_;

    // Private helper functions
    void loadText(AssetManager& assetManager);

};

#endif

