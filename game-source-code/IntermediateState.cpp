#include "IntermediateState.h"
#include "EndlessLevelState.h"
#include "LevelEditorState.h"

#include "Configuration.h"

IntermediateState::IntermediateState(gamePtr game, string mazeName, int lvlNumber): game_{game}, mazeName_{mazeName}, lvlNumber_{lvlNumber}
{
    // error checking
}

void IntermediateState::initialise()
{
    loadText(game_->assetManager);
}

void IntermediateState::processInput()
{
    sf::Event event;

    while (game_->window.pollEvent(event))
    {
        if (game_->inputManager.isExitRequest(event))
            game_->window.close();
        
        if (event.type == sf::Event::Resized)
            game_->view = game_->inputManager.getLetterboxView(game_->view, event.size.width, event.size.height);
    }
}

void IntermediateState::update(float dt)
{
    elapsedTime += dt;
    if (elapsedTime > INTER_DISPLAY_TIME*1000)
    {
        game_->stateMachine.addState(make_unique<EndlessLevelState>(game_,mazeName_,lvlNumber_));
    }
}

void IntermediateState::draw(float dt)
{
    game_->window.clear();
    game_->window.setView(game_->view);

    for (auto line : lines_)
        game_->window.draw(line);

    game_->window.display();
}

/*------------- Private helper functions -------------*/

void IntermediateState::loadText(AssetManager& assetManager)
{
    sf::Text line;
    line.setFont(*assetManager.getFont("coarse 8-bit"));
    line.setString("LEVEL " + to_string(lvlNumber_));
    line.setOrigin(line.getGlobalBounds().width/2,line.getGlobalBounds().height/2);
    line.setPosition(GAME_WIDTH/2, 2*GAME_HEIGHT/5);

    lines_.push_back(line);

    line.setFont(*assetManager.getFont("fine 8-bit"));
    line.setString("Maze: " + mazeName_);
    line.setOrigin(line.getGlobalBounds().width/2,line.getGlobalBounds().height/2);
    line.setPosition(GAME_WIDTH/2, 3*GAME_HEIGHT/5);

    lines_.push_back(line);

}
