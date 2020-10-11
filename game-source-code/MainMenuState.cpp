#include "MainMenuState.h"
#include "MazeSelectState.h"
#include "EndlessLevelState.h"
#include "LevelEditorState.h"
#include "HighScoreState.h"
#include "TutorialState.h"
#include "CreditsState.h"
#include "Configuration.h"

#include <iostream>

MainMenuState::MainMenuState(gamePtr game): game_{game}
{
    // error checking
}

void MainMenuState::initialise()
{
    if (game_->assetManager.getStatus("unravel") != sf::SoundSource::Status::Playing)
    {
        game_->assetManager.playSong("unravel");
        game_->assetManager.setLoop("unravel", true);
    }

    loadTitle(game_->assetManager);

    loadButtons(game_->assetManager);
}

void MainMenuState::processInput()
{
    sf::Event event;

    while (game_->window.pollEvent(event))
    {
        if (game_->inputManager.isExitRequest(event))
            game_->window.close();
        
        if (event.type == sf::Event::Resized)
            game_->view = game_->inputManager.getLetterboxView(game_->view, event.size.width, event.size.height);

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (playButton_.isHover(game_->window))
            {
                game_->assetManager.playSound("button click");
                game_->stateMachine.addState(make_unique<MazeSelectState>(game_));
            }

            if (levelEditorButton_.isHover(game_->window))
            {
                game_->assetManager.playSound("button click");
                game_->stateMachine.addState(make_unique<LevelEditorState>(game_));
            }

            if (highScoresButton_.isHover(game_->window))
            {
                game_->assetManager.playSound("button click");
                game_->stateMachine.addState(make_unique<HighScoreState>(game_));
            }

            if (how2PlayButton_.isHover(game_->window))
            {
                game_->assetManager.playSound("button click");
                game_->stateMachine.addState(make_unique<TutorialState>(game_));
            }

            if (creditsButton_.isHover(game_->window))
            {
                game_->assetManager.playSound("button click");
                game_->assetManager.stopSong("unravel");
                game_->stateMachine.addState(make_unique<CreditsState>(game_));
            }
        }
    }
}

void MainMenuState::update(float dt)
{
    playButton_.update(game_->window);
    levelEditorButton_.update(game_->window);
    highScoresButton_.update(game_->window);
    how2PlayButton_.update(game_->window);
    creditsButton_.update(game_->window);
}

void MainMenuState::draw(float dt)
{
    game_->window.clear();
    game_->window.setView(game_->view);

    game_->window.draw(bg);
    game_->window.draw(title_);
    game_->window.draw(playButton_);
    game_->window.draw(levelEditorButton_);
    game_->window.draw(highScoresButton_);
    game_->window.draw(how2PlayButton_);
    game_->window.draw(creditsButton_);

    game_->window.display();
}

/*------------- Private helper functions -------------*/

void MainMenuState::loadTitle(AssetManager& assetManager)
{
    title_.setFont(*assetManager.getFont("coarse 8-bit"));
    title_.setString("Harambe's Quest");
    title_.setOrigin(title_.getGlobalBounds().width/2.f, title_.getGlobalBounds().height/2.f);
    title_.setPosition(GAME_WIDTH/2.f, 80.f);
    title_.setScale(1.6f, 1.6f);
    title_.setFillColor(sf::Color::White);
    
    // Background
    bg.setTexture(*assetManager.getTexture("menu background"));
}

void MainMenuState::loadButtons(AssetManager& assetManager)
{
    auto font = assetManager.getFont("coarse 8-bit");
    auto texture = assetManager.getTexture("menu button");
    auto spriteScale = 0.8f;
    auto offset = 200.f;
    auto buttonSpacing = 150.f;

    playButton_ = Button{texture, font};
    playButton_.setString("PLAY");
    playButton_.setPosition(sf::Vector2f{GAME_WIDTH/2, offset});
    playButton_.setSpriteScale(spriteScale, spriteScale);

    levelEditorButton_ = Button{texture, font};
    levelEditorButton_.setString("  MAZE \nEDITOR");
    levelEditorButton_.setPosition(sf::Vector2f{GAME_WIDTH/2, offset + buttonSpacing});
    levelEditorButton_.setSpriteScale(spriteScale, spriteScale);
    levelEditorButton_.setTextScale(0.8f, 0.8f);

    highScoresButton_ = Button{texture, font};
    highScoresButton_.setString("  HIGH\nSCORES");
    highScoresButton_.setPosition(sf::Vector2f{GAME_WIDTH/2, offset + 2*buttonSpacing});
    highScoresButton_.setSpriteScale(spriteScale, spriteScale);
    highScoresButton_.setTextScale(0.8f, 0.8f);

    how2PlayButton_ = Button{texture, font};
    how2PlayButton_.setString(" HOW TO \n   PLAY");
    how2PlayButton_.setPosition(sf::Vector2f{GAME_WIDTH/2, offset + 3*buttonSpacing});
    how2PlayButton_.setSpriteScale(spriteScale, spriteScale);
    how2PlayButton_.setTextScale(0.8f, 0.8f);

    creditsButton_ = Button{texture, font};
    creditsButton_.setString("CREDITS");
    creditsButton_.setPosition(sf::Vector2f{GAME_WIDTH/2, offset + 4*buttonSpacing});
    creditsButton_.setSpriteScale(spriteScale, spriteScale);
    creditsButton_.setTextScale(0.8f, 0.8f);

}
