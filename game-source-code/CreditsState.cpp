#include "CreditsState.h"
#include "MainMenuState.h"

#include "Configuration.h"

#include <string>

CreditsState::CreditsState(gamePtr game): game_{game}
{
    // error checking
}

void CreditsState::initialise()
{
    loadTitle(game_->assetManager);
    loadText(game_->assetManager);
    loadButtons(game_->assetManager);
    loadPageProgress(game_->assetManager);

    game_->assetManager.playSong("rick roll");
    game_->assetManager.setLoop("rick roll", true);
}

void CreditsState::processInput()
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
                game_->assetManager.playSound("button click");
                game_->stateMachine.addState(make_unique<MainMenuState>(game_));
                game_->assetManager.stopSong("rick roll");
            }

            if (rightButton_.isHover(game_->window))
                nextPage();

            if (leftButton_.isHover(game_->window))
                previousPage();
        }
    }
}

void CreditsState::update(float dt)
{
    exitButton_.update(game_->window);
    leftButton_.update(game_->window);
    rightButton_.update(game_->window);
}

void CreditsState::draw(float dt)
{
    game_->window.clear();
    game_->window.setView(game_->view);

    game_->window.draw(bg);
    game_->window.draw(title_);

    for (const auto& line : pages_[pageNum_])
            game_->window.draw(line);

    game_->window.draw(pageDisplay_);

    game_->window.draw(exitButton_);
    game_->window.draw(leftButton_);
    game_->window.draw(rightButton_);


    game_->window.display();
}

/*------------- Private helper functions -------------*/

void CreditsState::loadTitle(AssetManager& assetManager)
{
    title_.setFont(*assetManager.getFont("pressStart 8-bit"));

    title_.setString("CREDITS");
    title_.setOrigin(title_.getGlobalBounds().width/2, title_.getGlobalBounds().height/2);
    title_.setPosition(GAME_WIDTH/2, 50);
    title_.setFillColor(sf::Color{21, 244, 238});

    // background
    bg.setTexture(*assetManager.getTexture("aux background"));
}

void CreditsState::loadText(AssetManager& assetManager)
{
    sf::Text line;
    vector<sf::Text> paragraph;

    line.setFont(*assetManager.getFont("fine 8-bit"));

    assetManager.loadCredits();
    vector<string> credits = assetManager.getCredits();

    for (int i = 0; i< 15; i++)
    {
        line.setString(credits[i]);
        paragraph.push_back(line);
        paragraph[i].setScale(0.7,0.7);
        paragraph[i].setOrigin(0.f, paragraph[i].getGlobalBounds().height/2);
        paragraph[i].setPosition(40 ,125.f + i*40.f);
    }

    pages_.push_back(paragraph);

    paragraph.clear();

    for (int j = 15; j<31; j++)
    {   int i = j-15;
        line.setString(credits[j]);
        paragraph.push_back(line);
        paragraph[i].setScale(0.7,0.7);
        paragraph[i].setOrigin(0.f, paragraph[i].getGlobalBounds().height/2);
        paragraph[i].setPosition(40 ,125.f + i*40.f);
    }

    pages_.push_back(paragraph);

    paragraph.clear();

    for (int j = 31; j< 49; j++)
    {   int i = j-31;
        line.setString(credits[j]);
        paragraph.push_back(line);
        paragraph[i].setScale(0.7,0.7);
        paragraph[i].setOrigin(0.f, paragraph[i].getGlobalBounds().height/2);
        paragraph[i].setPosition(40 ,125.f + i*40.f);
    }

    pages_.push_back(paragraph);

}

void CreditsState::loadButtons(AssetManager& assetManager)
{
    auto font = assetManager.getFont("coarse 8-bit");
    auto texture = assetManager.getTexture("menu button");

    exitButton_ = Button{assetManager.getTexture("exit button")};
    exitButton_.setPosition(sf::Vector2f{800,32});  // hard-coded for now
    exitButton_.setHoverColour(sf::Color::Red);

    leftButton_ = Button{assetManager.getTexture("left triangle")};
    leftButton_.setPosition(GAME_WIDTH/2 - 90.f, 850);
    leftButton_.setSpriteScale(0.4f,0.4f);

    rightButton_ = Button{assetManager.getTexture("right triangle")};
    rightButton_.setPosition(GAME_WIDTH/2 + 95.f, 850);
    rightButton_.setSpriteScale(0.4f,0.4f);
}

void CreditsState::loadPageProgress(AssetManager& assetManager)
{
    pageDisplay_.setFont(*assetManager.getFont("pressStart 8-bit"));
    pageDisplay_.setString(to_string(pageNum_ + 1) + "/" + to_string(pages_.size()));
    pageDisplay_.setOrigin(pageDisplay_.getGlobalBounds().width/2, pageDisplay_.getGlobalBounds().height/2);
    pageDisplay_.setScale(0.8, 0.8);
    pageDisplay_.setPosition(GAME_WIDTH/2, 850);
}

void CreditsState::nextPage()
{
    if (pageNum_ == pages_.size() - 1)
    {
        game_->assetManager.playSound("error");
    }
    else
    {
        game_->assetManager.playSound("button click");

        pageNum_++;
        pageDisplay_.setString(to_string(pageNum_ + 1) + "/" + to_string(pages_.size()));
        pageDisplay_.setOrigin(pageDisplay_.getGlobalBounds().width/2, pageDisplay_.getGlobalBounds().height/2);
    }
}

void CreditsState::previousPage()
{
    if (pageNum_ == 0)
    {
        game_->assetManager.playSound("error");
    }
    else
    {
        game_->assetManager.playSound("button click");

        pageNum_--;
        pageDisplay_.setString(to_string(pageNum_ + 1) + "/" + to_string(pages_.size()));
        pageDisplay_.setOrigin(pageDisplay_.getGlobalBounds().width/2, pageDisplay_.getGlobalBounds().height/2);
    }
}
