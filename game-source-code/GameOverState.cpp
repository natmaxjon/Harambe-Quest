#include "GameOverState.h"
#include "EndlessLevelState.h"
#include "MainMenuState.h"
#include "IntermediateState.h"
#include "HighScoreState.h"

#include "Configuration.h"
#include "Scoreboard.h"
#include <iostream>
#include <string>

GameOverState::GameOverState(gamePtr game, string mazeName, int lvlNumber): game_{game}, mazeName_{mazeName}, lvlNumber_{lvlNumber}
{
    // error checking
}

void GameOverState::initialise()
{

    loadButtons(game_->assetManager);
    loadText(game_->assetManager);
    loadScoreBoard(game_->assetManager);
    loadScoreText(game_->assetManager);
    loadSprites(game_->assetManager);

    soundBoard_ = Soundboard{game_, enterName_};
}

void GameOverState::processInput()
{
    sf::Event event;

    while (game_->window.pollEvent(event))
    {
        if (game_->inputManager.isExitRequest(event))
            game_->window.close();
        
        if (event.type == sf::Event::Resized)
            game_->view = game_->inputManager.getLetterboxView(game_->view, event.size.width, event.size.height);

        if (enterName_)
        {
           if (event.type == sf::Event::TextEntered)
            {
                if (isValid(event.text.unicode))
                {
                    if (nameEntered_.size() < 5)
                        nameEntered_+= toupper(static_cast<char>(event.text.unicode));
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace)
            {
                if (nameEntered_.size() > 0)
                    nameEntered_.erase(nameEntered_.size() - 1);
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (restartButton_.isHover(game_->window))
            {
                updateScores(game_->assetManager);
                game_->assetManager.playSound("button click");
                game_->stateMachine.addState(make_unique<IntermediateState>(game_, mazeName_, 1));
                soundBoard_.restart();
            }

            if (mainMenuButton_.isHover(game_->window))
            {
                soundBoard_.gotoMenu();
                game_->assetManager.playSound("button click");
                updateScores(game_->assetManager);
                game_->stateMachine.addState(make_unique<MainMenuState>(game_));
            }

            if (highScoresButton_.isHover(game_->window))
            {
                updateScores(game_->assetManager);
                game_->assetManager.playSound("button click");
                game_->stateMachine.addState(make_unique<HighScoreState>(game_));
            }

        }
    }
}

void GameOverState::update(float dt)
{
    elapsedTime_ += dt;
    int animFrame1 = static_cast<int>((elapsedTime_ /tStep_) * frameCount_) % frameCount_;
    auto textureString = "coffin" + to_string(animFrame1);
    coffinDancers_.setTexture(*game_->assetManager.getTexture(textureString.c_str()));
    
    int animFrame2 = static_cast<int>((elapsedTime_ /tStep1_) * frameCount1_) % frameCount1_;
    textureString = "petal" + to_string(animFrame2);
    petals_.setTexture(*game_->assetManager.getTexture(textureString.c_str()));
    
    restartButton_.update(game_->window);
    mainMenuButton_.update(game_->window);
    highScoresButton_.update(game_->window);
    
    if (enterName_)
        updateNameEntered();

}

void GameOverState::draw(float dt)
{
    game_->window.clear(sf::Color{0,23,45});
    game_->window.setView(game_->view);
    
    game_->window.draw(restartButton_);
    game_->window.draw(mainMenuButton_);
    game_->window.draw(highScoresButton_);
    game_->window.draw(text_);
    game_->window.draw(scoreText_);
    
    if (enterName_)
    {
        game_->window.draw(petals_);
        game_->window.draw(piaoPiao_);
        game_->window.draw(sakuraTree_);
        
        game_->window.draw(nameDisplay_);
    }
    else
    {
        game_->window.draw(grass_);
        game_->window.draw(coffinDancers_);
    }
    
    game_->window.display();

}

/*------------- Private helper functions -------------*/

void GameOverState::loadButtons(AssetManager& assetManager)
{
    auto font = assetManager.getFont("coarse 8-bit");
    auto texture = assetManager.getTexture("menu button");

    restartButton_ = Button{texture, font};
    restartButton_.setString(" PLAY\nAGAIN");
    restartButton_.setPosition(sf::Vector2f{2*GAME_WIDTH/10, 3*GAME_HEIGHT/5 - 100});
    restartButton_.setTextScale(0.8, 0.8);
    restartButton_.setSpriteScale(0.8, 0.8);
    restartButton_.setHoverColour(sf::Color::Yellow);

    mainMenuButton_ = Button{texture, font};
    mainMenuButton_.setString("MAIN\nMENU");
    mainMenuButton_.setPosition(sf::Vector2f{5*GAME_WIDTH/10, 3*GAME_HEIGHT/5 - 100});
    mainMenuButton_.setTextScale(0.8, 0.8);
    mainMenuButton_.setSpriteScale(0.8, 0.8);
    mainMenuButton_.setHoverColour(sf::Color::Yellow);

    highScoresButton_ = Button{texture, font};
    highScoresButton_.setString("   HIGH \nSCORES");
    highScoresButton_.setPosition(sf::Vector2f{8*GAME_WIDTH/10, 3*GAME_HEIGHT/5 - 100});
    highScoresButton_.setTextScale(0.8, 0.8);
    highScoresButton_.setSpriteScale(0.8, 0.8);
    highScoresButton_.setHoverColour(sf::Color::Yellow);

}

void GameOverState::loadText(AssetManager& assetManager)
{
    text_.setFont(*assetManager.getFont("coarse 8-bit"));
    text_.setString("GAME OVER!!!");
    text_.setOrigin(text_.getGlobalBounds().width/2.0f,
                    text_.getGlobalBounds().height/2.0f);
    text_.setPosition(GAME_WIDTH/2, GAME_HEIGHT/10);
}

void GameOverState::loadScoreText(AssetManager& assetManager)
{
    scoreText_.setFont(*assetManager.getFont("coarse 8-bit"));
    scoreText_.setString("Your Score: " + to_string(Scoreboard::getEndScore()));
    scoreText_.setOrigin(scoreText_.getGlobalBounds().width/2.f,
                         scoreText_.getGlobalBounds().height/2.f);
    scoreText_.setPosition(GAME_WIDTH/2, text_.getPosition().y + 100.f);


    nameDisplay_.setFont(*assetManager.getFont("coarse 8-bit"));
}

void GameOverState::updateNameEntered()
{
    std::string text = nameEntered_;

    for (int i = text.size(); i < 5; i++)
        text += '_';

    text = "Your Name: " + text;
    nameDisplay_.setString(text);
    nameDisplay_.setOrigin(nameDisplay_.getGlobalBounds().width/2.0f,
                           nameDisplay_.getGlobalBounds().height/2.0f);
    nameDisplay_.setPosition(GAME_WIDTH/2, scoreText_.getPosition().y + 100.f);
}

void GameOverState::loadScoreBoard(AssetManager& assetManager)
{
    assetManager.loadHighScores(mazeName_);

    auto highscores = assetManager.getHighScores();

    scoreBoard_ = Scoreboard{highscores};

    if (Scoreboard::getEndScore() > scoreBoard_.getFifthScore())
    {
        enterName_ = true;
    } else
    {
        enterName_ = false;
    }
}

void GameOverState::loadSprites(AssetManager& assetManager)
{
    coffinDancers_.setPosition(150.f, 400.f);
    
    piaoPiao_.setTexture(*assetManager.getTexture("piao piao"));
    piaoPiao_.setOrigin(piaoPiao_.getGlobalBounds().width/2.f, piaoPiao_.getGlobalBounds().height);
    piaoPiao_.setPosition(120.f, GAME_HEIGHT);
    piaoPiao_.setScale(3.f, 3.f);

    sakuraTree_.setTexture(*assetManager.getTexture("sakura tree"));
    sakuraTree_.setOrigin(sakuraTree_.getGlobalBounds().width, sakuraTree_.getGlobalBounds().height);
    sakuraTree_.setPosition(GAME_WIDTH, GAME_HEIGHT);
    sakuraTree_.setScale(1.5f, 1.5f);
    
    petals_.setTexture(*assetManager.getTexture("petal0"));
    petals_.setOrigin(petals_.getGlobalBounds().width, petals_.getGlobalBounds().height);
    petals_.setPosition(GAME_WIDTH, GAME_HEIGHT);
    petals_.setScale(1.5f, 1.5f);

    bgTexture_ = *assetManager.getTexture("grass");
    bgTexture_.setRepeated(true);
    grass_.setTexture(bgTexture_);
    grass_.setPosition(0.f, 720.f);
    grass_.setTextureRect(sf::IntRect(0.f, 720.f, GAME_WIDTH, GAME_HEIGHT - 720.f));
}

bool GameOverState::isValid(uint32_t unicode)
{
    if (unicode < 65)
        return false;

    if (unicode > 122)
        return false;

    if (unicode > 90 && unicode < 97)
        return false;

    return true;
}

void GameOverState::updateScores(AssetManager& assetManager)
{
    scoreBoard_.updateHighScores(nameEntered_);

    if (enterName_)
    {
       assetManager.writeHighScores(scoreBoard_.getHighScores(), mazeName_);
    }
}
