#include "GameLoop.h"

#include "Configuration.h"
#include "SplashState.h"
#include "icon1024.h"

// Temporary
//#include "TutorialState.h"
//#include "LevelEditorState.h"

GameLoop::GameLoop(float width, float height, const string& title, sf::Uint32 style)
{
    game_->window.create(sf::VideoMode(width, height), title, style);
    game_->window.setIcon( icon.width,  icon.height, icon.pixel_data );

    game_->window.setVerticalSyncEnabled(true);

    // The first state is always the splash screen
    game_->stateMachine.addState(make_unique<SplashState>(game_));
}

void GameLoop::run()
{
    srand(time(NULL));

    previousTime_ = clock_.getElapsedTime().asMilliseconds();

    while(game_->window.isOpen())
    {
        // Determine how far behind the game's clock is
        currentTime_ = clock_.getElapsedTime().asMilliseconds();
        elapsedTime_ = currentTime_ - previousTime_;
        previousTime_ = currentTime_;
        lag_ += elapsedTime_;

        game_->stateMachine.handleStateChange();

        game_->stateMachine.getCurrentState()->processInput();

        // Catch up to current frame (CHANGE: ADD MAX ITERATIONS AS A FAIL SAFE)
        while (lag_ >= MS_PER_FRAME)
        {
            game_->stateMachine.getCurrentState()->update(MS_PER_FRAME);
            lag_ -= MS_PER_FRAME;
        }

        game_->stateMachine.getCurrentState()->draw(lag_/MS_PER_FRAME);
    }
}
