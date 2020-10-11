#include "TutorialState.h"
#include "MainMenuState.h"

#include "Configuration.h"

#include <string>

TutorialState::TutorialState(gamePtr game): game_{game}
{
    // error checking
}

void TutorialState::initialise()
{
    loadTitle(game_->assetManager);
    loadText(game_->assetManager);
    loadButtons(game_->assetManager);
    loadPageProgress(game_->assetManager);
    loadKey(game_->assetManager);
}

void TutorialState::processInput()
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
            }

            if (rightButton_.isHover(game_->window))
                nextPage();

            if (leftButton_.isHover(game_->window))
                previousPage();
        }
    }
}

void TutorialState::update(float dt)
{
    exitButton_.update(game_->window);
    leftButton_.update(game_->window);
    rightButton_.update(game_->window);
}

void TutorialState::draw(float dt)
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

    drawKey();

    game_->window.display();
}

/*------------- Private helper functions -------------*/

void TutorialState::loadTitle(AssetManager& assetManager)
{
    title_.setFont(*assetManager.getFont("pressStart 8-bit"));

    title_.setString("HOW TO PLAY");
    title_.setOrigin(title_.getGlobalBounds().width/2, title_.getGlobalBounds().height/2);
    title_.setPosition(GAME_WIDTH/2, 50);
    title_.setFillColor(sf::Color{21, 244, 238});

    // background
    bg.setTexture(*assetManager.getTexture("aux background"));
}

void TutorialState::loadText(AssetManager& assetManager)
{
    sf::Text line;
    vector<sf::Text> paragraph;

    line.setFont(*assetManager.getFont("fine 8-bit"));

    line.setString("Welcome to HARAMBE'S QUEST!\n\n");
    paragraph.push_back(line);

    line.setString("You play as the beloved gorilla, Harambe, and your goal is\n");
    paragraph.push_back(line);

    line.setString("to eat all the food in the zoo before the wardens catch\n");
    paragraph.push_back(line);

    line.setString("you! Below is a key showing the names for various objects\n");
    paragraph.push_back(line);

    line.setString("you will see in the zoo. We will see how each of them work in\n");
    paragraph.push_back(line);

    line.setString("the upcoming pages.\n");
    paragraph.push_back(line);

    for (int i = 0; i< paragraph.size(); i++)
    {
        paragraph[i].setScale(0.7,0.7);
        paragraph[i].setOrigin(0.f, paragraph[i].getGlobalBounds().height/2);
        paragraph[i].setPosition(25 ,125.f + i*40.f);
    }

    pages_.push_back(paragraph);

    paragraph.clear();

    line.setString("- Use the arrow keys to move Harambe around the zoo\n");
    paragraph.push_back(line);

    line.setString("- Eat all the fruit and pills while avoiding the wardens\n");
    paragraph.push_back(line);

    line.setString("- Collect the keys to unlock the corresponding gates\n");
    paragraph.push_back(line);

    line.setString("- Eating the pills will grant Harambe special abilities for a\n");
    paragraph.push_back(line);

    line.setString("  short amount time\n");
    paragraph.push_back(line);

    line.setString("- Eating a red pill enrages Harambe. His eyes will turn red\n");
    paragraph.push_back(line);

    line.setString("  and he can punch wardens back to the centre of the zoo\n");
    paragraph.push_back(line);

    line.setString("- Eating a blue pill will given Harambe the strength to\n");
    paragraph.push_back(line);

    line.setString("  break through the gates without keys, and walk over the\n");
    paragraph.push_back(line);

    line.setString("  wardens without getting caught\n");
    paragraph.push_back(line);

    line.setString("- You can get caught a total of 3 times per level before\n");
    paragraph.push_back(line);

    line.setString("  you lose the game\n");
    paragraph.push_back(line);

    line.setString("- Fruit is worth 50 pts, pills are worth 100 pts and punching\n");
    paragraph.push_back(line);

    line.setString("  a warden is worth 200 pts, which increases as you\n");
    paragraph.push_back(line);

    line.setString("  punch more.\n");
    paragraph.push_back(line);

    line.setString("- If your score is within the top 5 for a particular maze, you\n");
    paragraph.push_back(line);

    line.setString("  will be able to enter your name and your result will be \n");
    paragraph.push_back(line);

    line.setString("  displayed in the HIGHSCORES section\n");
    paragraph.push_back(line);

    for (int i = 0; i< paragraph.size(); i++)
    {
        paragraph[i].setScale(0.7,0.7);
        paragraph[i].setOrigin(0.f, paragraph[i].getGlobalBounds().height/2);
        paragraph[i].setPosition(25 ,125.f + i*40.f);
    }

    pages_.push_back(paragraph);

    paragraph.clear();

    line.setString("- While playing in the maze, press 'P' to change to the next\n");
    paragraph.push_back(line);

    line.setString("  song and press 'O' to change to the previous song\n");
    paragraph.push_back(line);

    line.setString("- Press Esc to close the game at any time\n");
    paragraph.push_back(line);

    line.setString("\n\n\n\n\n\n");
    paragraph.push_back(line);

    line.setString("NOTE: You also have access to a MAZE EDITOR, which allows\n");
    paragraph.push_back(line);

    line.setString("you to create your own custom maze designs to play in.\n");
    paragraph.push_back(line);

    line.setString("This has its own dedicated help section that can be \n");
    paragraph.push_back(line);

    line.setString("accessed by pressing the question mark from within the\n");
    paragraph.push_back(line);

    line.setString("editor itself\n");
    paragraph.push_back(line);

    for (int i = 0; i< paragraph.size(); i++)
    {
        paragraph[i].setScale(0.7,0.7);
        paragraph[i].setOrigin(0.f, paragraph[i].getGlobalBounds().height/2);
        paragraph[i].setPosition(25 ,125.f + i*40.f);
    }

    pages_.push_back(paragraph);
}

void TutorialState::loadButtons(AssetManager& assetManager)
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

void TutorialState::loadPageProgress(AssetManager& assetManager)
{
    pageDisplay_.setFont(*assetManager.getFont("pressStart 8-bit"));
    pageDisplay_.setString(to_string(pageNum_ + 1) + "/" + to_string(pages_.size()));
    pageDisplay_.setOrigin(pageDisplay_.getGlobalBounds().width/2, pageDisplay_.getGlobalBounds().height/2);
    pageDisplay_.setScale(0.8, 0.8);
    pageDisplay_.setPosition(GAME_WIDTH/2, 850);
}

void TutorialState::loadKey(AssetManager& assetManager)
{
    sf::Sprite sprite;
    sf:: Text label;

    label.setFont(*assetManager.getFont("pressStart 8-bit"));
    label.setScale(0.6, 0.6);

    sprite = sf::Sprite{*assetManager.getTexture("wall")};
    label.setString("WALL");
    keySprites_.push_back(sprite);
    keyLabels_.push_back(label);

    sprite = sf::Sprite{*assetManager.getTexture("corner")};
    label.setString("CORNER");
    keySprites_.push_back(sprite);
    keyLabels_.push_back(label);

    sprite = sf::Sprite{*assetManager.getTexture("gate")};
    label.setString("GATE");
    keySprites_.push_back(sprite);
    keyLabels_.push_back(label);

    sprite = sf::Sprite{*assetManager.getTexture("broken gate")};
    label.setString("BROKEN GATE");
    keySprites_.push_back(sprite);
    keyLabels_.push_back(label);

    sprite = sf::Sprite{*assetManager.getTexture("key")};
    label.setString("KEY");
    keySprites_.push_back(sprite);
    keyLabels_.push_back(label);

    sprite = sf::Sprite{*assetManager.getTexture("fruit")};
    label.setString("FRUIT");
    keySprites_.push_back(sprite);
    keyLabels_.push_back(label);

    sprite = sf::Sprite{*assetManager.getTexture("power pellet")};
    label.setString("RED PILL");
    keySprites_.push_back(sprite);
    keyLabels_.push_back(label);

    sprite = sf::Sprite{*assetManager.getTexture("super pellet")};
    label.setString("BLUE PILL");
    keySprites_.push_back(sprite);
    keyLabels_.push_back(label);

    for (auto i = 0; i < keySprites_.size(); i++)
    {
        keySprites_[i].setOrigin(keySprites_[i].getGlobalBounds().width/2.f,
                                 keySprites_[i].getGlobalBounds().height/2.f);
        keySprites_[i].setScale(1,1);
        keySprites_[i].setPosition(GAME_WIDTH/2.f - 30.f - 50.f,400.f + i*50.f);

        keyLabels_[i].setOrigin(0.f, keyLabels_[i].getGlobalBounds().height/2.f);
        keyLabels_[i].setPosition(GAME_WIDTH/2.f + 30.f - 50.f, 400.f + i*50.f);
    }
}

void TutorialState::drawKey()
{
    if (pageNum_ != 0)
        return;

    for (auto i = 0; i < keySprites_.size(); i++)
    {
        game_->window.draw(keyLabels_[i]);
        game_->window.draw(keySprites_[i]);
    }
}

void TutorialState::nextPage()
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

void TutorialState::previousPage()
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
