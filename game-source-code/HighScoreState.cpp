#include "HighScoreState.h"
#include "MainMenuState.h"

#include "Configuration.h"

HighScoreState::HighScoreState(gamePtr game): game_{game}
{
    // error checking
}

void HighScoreState::initialise()
{
    loadButtons(game_->assetManager);
    loadTitle(game_->assetManager);
    loadMazes(game_->assetManager);

}

void HighScoreState::processInput()
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
            if (exitButton_.isHover(game_->window))
            {
                checkMusic();
                game_->stateMachine.addState(make_unique<MainMenuState>(game_));
                game_->assetManager.playSound("button click");
            }

            if (rightButton_.isHover(game_->window))
                nextMaze();

            if (leftButton_.isHover(game_->window))
                previousMaze();
        }
    }
}

void HighScoreState::update(float dt)
{
    timeFlash += dt;
    auto tFlash = 1200;
    auto colors = vector<sf::Color>{Gold,sf::Color::White, Silver,sf::Color::White, Bronze, sf::Color::White};
    auto col = static_cast<int>((timeFlash/tFlash) * 6) % 6;

    title_.setFillColor(colors[col]);
    background.setColor(colors[col]);

    exitButton_.update(game_->window);

    if (mazeIt != mazeNames_.begin())
        leftButton_.setHoverColour(sf::Color::Yellow);
    else
        leftButton_.setHoverColour(sf::Color::Red);


    if (mazeIt+1 != mazeNames_.end())
        rightButton_.setHoverColour(sf::Color::Yellow);
    else
        rightButton_.setHoverColour(sf::Color::Red);


    rightButton_.update(game_->window);
    leftButton_.update(game_->window);
}

void HighScoreState::draw(float dt)
{
    game_->window.clear();
    game_->window.setView(game_->view);

    game_->window.draw(background);
    game_->window.draw(exitButton_);
    game_->window.draw(rightButton_);
    game_->window.draw(leftButton_);

    game_->window.draw(title_);

    game_->window.draw(mazeDisplay_);

    for (auto item : entries)
    {
        game_->window.draw(item);
    }

    game_->window.display();
}

/*------------- Private helper functions -------------*/

void HighScoreState::loadButtons(AssetManager& assetManager)
{
    exitButton_ = Button{assetManager.getTexture("exit button")};
    exitButton_.setPosition(sf::Vector2f{800,32});  // hard-coded for now
    exitButton_.setHoverColour(sf::Color::Red);

    leftButton_ = Button{assetManager.getTexture("left triangle")};
    leftButton_.setPosition(sf::Vector2f{40.f, GAME_HEIGHT/2});
    leftButton_.setSpriteScale(0.5f,0.5f);

    rightButton_ = Button{assetManager.getTexture("right triangle")};
    rightButton_.setPosition(GAME_WIDTH - 40.f, GAME_HEIGHT/2);
    rightButton_.setSpriteScale(0.5f,0.5f);
}

void HighScoreState::loadTitle(AssetManager& assetManager)
{
    title_.setFont(*assetManager.getFont("coarse 8-bit"));
    title_.setString("HIGH SCORES");

    title_.setOrigin(title_.getGlobalBounds().width/2.0f,
                         title_.getGlobalBounds().height/2.0f);
    title_.setPosition(GAME_WIDTH/2, GAME_HEIGHT/5);
    title_.setScale(1.1,1.1);

    background.setTexture(*assetManager.getTexture("hs background"));
}

void HighScoreState::loadMazes(AssetManager& assetManager)
{
    assetManager.loadMazeList();
    mazeNames_ = assetManager.getMazeList();

    mazeIt = mazeNames_.begin();

    loadHighScores(game_->assetManager);
}

void HighScoreState::nextMaze()
{
    if (mazeIt+1 != mazeNames_.end())
    {
        mazeIt++;
        game_->assetManager.playSound("button click");
    } else
    {
        game_->assetManager.playSound("error");
        return;
    }

    loadHighScores(game_->assetManager);
}

void HighScoreState::previousMaze()
{
    if (mazeIt != mazeNames_.begin())
    {
        mazeIt--;
        game_->assetManager.playSound("button click");
    } else
    {
        game_->assetManager.playSound("error");
        return;
    }

    loadHighScores(game_->assetManager);
}

void HighScoreState::checkMusic()
{
    if (game_->assetManager.getStatus("xue hua piao") == sf::SoundSource::Status::Playing)
    {
        game_->assetManager.stopSong("xue hua piao");
    }

    if (game_->assetManager.getStatus("coffin dance") == sf::SoundSource::Status::Playing)
    {
        game_->assetManager.stopSong("coffin dance");
    }
}

void HighScoreState::loadHighScores(AssetManager& assetManager)
{
    currentMaze_ = *mazeIt;

    assetManager.loadHighScores(currentMaze_);
    auto highscores = assetManager.getHighScores();

    entries.clear();

    mazeDisplay_.setFont(*assetManager.getFont("fine 8-bit"));
    mazeDisplay_.setString("Maze: " + currentMaze_);
    mazeDisplay_.setOrigin(mazeDisplay_.getGlobalBounds().width/2.0f,
                           mazeDisplay_.getGlobalBounds().height/2.0f);
    mazeDisplay_.setPosition(GAME_WIDTH/2, 2*GAME_HEIGHT/5);
    mazeDisplay_.setScale(1.f,1.f);

    sf::Text entry;
    entry.setFont(*assetManager.getFont("fine 8-bit"));

    for (int i = 0; i < 5; i++)
    {
        entry.setString(to_string(i+1) + "\t" + highscores[i].first + "\t" + to_string(highscores[i].second));
        entry.setOrigin(entry.getGlobalBounds().width/2.0f,
                         entry.getGlobalBounds().height/2.0f);
        entry.setPosition(GAME_WIDTH/2, 2*GAME_HEIGHT/5 + 75.f*(i+1));
        entry.setScale(0.9f,0.9f);
        entries.push_back(entry);
    }


    entries[0].setFillColor(Gold);
    entries[1].setFillColor(Silver);
    entries[2].setFillColor(Bronze);
}
