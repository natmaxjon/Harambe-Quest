#include "MazeSelectState.h"
#include "MainMenuState.h"
#include "IntermediateState.h"
#include "Soundboard.h"
#include "Configuration.h"

#include <iostream>

MazeSelectState::MazeSelectState(gamePtr game): game_{game}
{
    // error checking
}

void MazeSelectState::initialise()
{
    loadButtons(game_->assetManager);
    loadTitle(game_->assetManager);
    loadMazes(game_->assetManager);
    loadCharacters(game_->assetManager);
}

void MazeSelectState::processInput()
{
    sf::Event event;

    while (game_->window.pollEvent(event))
    {
        if (game_->inputManager.isExitRequest(event))
            game_->window.close();

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (exitButton_.isHover(game_->window))
            {
                game_->assetManager.playSound("button click");
                game_->stateMachine.addState(make_unique<MainMenuState>(game_));
            }

            if (rightButton_.isHover(game_->window))
                nextMaze();

            if (leftButton_.isHover(game_->window))
                previousMaze();

            if (playButton_.isHover(game_->window))
            {
                game_->assetManager.stopSong("unravel");
                game_->assetManager.playSound("button click");

                Soundboard::shufflePlaylist();
                game_->assetManager.playSong(Soundboard::getPlaylist()[0]);
                game_->stateMachine.addState(make_unique<IntermediateState>(game_, currentMaze_, 1));
            }
            
            if (deleteButton_.isHover(game_->window))
                deleteMaze();
        }
    }
}

void MazeSelectState::update(float dt)
{
    exitButton_.update(game_->window);

    if (mazeIt != mazeNames_.begin() && mazeIt != mazeNames_.begin()+1)
    {
        leftButton_.setHoverColour(sf::Color::Yellow);
        deleteButton_.setHoverColour(sf::Color::Yellow);
        
        playButton_.setPosition(GAME_WIDTH/2 - 100, 850.f);
        deleteButton_.setPosition(GAME_WIDTH/2 + 100, 850.f);
    }
    else
    {
        leftButton_.setHoverColour(sf::Color::Red);
        
        deleteButton_.setPosition(2000.f, 2000.f);
        playButton_.setPosition(GAME_WIDTH/2, 850.f);
    }


    if (mazeIt+1 != mazeNames_.end())
        rightButton_.setHoverColour(sf::Color::Yellow);
    else
        rightButton_.setHoverColour(sf::Color::Red);


    rightButton_.update(game_->window);
    leftButton_.update(game_->window);
    playButton_.update(game_->window);
    deleteButton_.update(game_->window);
}

void MazeSelectState::draw(float dt)
{
    game_->window.clear(sf::Color{26,26,26});

    game_->window.draw(exitButton_);
    game_->window.draw(rightButton_);
    game_->window.draw(leftButton_);
    game_->window.draw(playButton_);
    game_->window.draw(deleteButton_);

    drawMaze();

    game_->window.draw(mazeDisplayName_);

    game_->window.display();
}

/*------------- Private helper functions -------------*/

void MazeSelectState::loadButtons(AssetManager& assetManager)
{
    exitButton_ = Button{assetManager.getTexture("exit button")};
    exitButton_.setPosition(sf::Vector2f{800,32});
    exitButton_.setHoverColour(sf::Color::Red);

    leftButton_ = Button{assetManager.getTexture("left triangle")};
    leftButton_.setPosition(sf::Vector2f{40.f, GAME_HEIGHT/2});
    leftButton_.setSpriteScale(0.5f,0.5f);

    rightButton_ = Button{assetManager.getTexture("right triangle")};
    rightButton_.setPosition(GAME_WIDTH - 40.f, GAME_HEIGHT/2);
    rightButton_.setSpriteScale(0.5f,0.5f);

    auto font = assetManager.getFont("coarse 8-bit");
    auto texture = assetManager.getTexture("menu button");

    playButton_ = Button{texture, font};
    playButton_.setString("PLAY");
    playButton_.setPosition(GAME_WIDTH/2 - 100, 850.f);
    playButton_.setSpriteScale(0.5f, 0.5f);
    playButton_.setTextScale(0.5f, 0.5f);
    
    deleteButton_ = Button{texture, font};
    deleteButton_.setString("DELETE");
    deleteButton_.setPosition(GAME_WIDTH/2 + 100, 850.f);
    deleteButton_.setSpriteScale(0.5f, 0.5f);
    deleteButton_.setTextScale(0.5f, 0.5f);
    
}

void MazeSelectState::loadTitle(AssetManager& assetManager)
{
    mazeDisplayName_.setFont(*assetManager.getFont("fine 8-bit"));
    mazeDisplayName_.setString(currentMaze_);
    mazeDisplayName_.setOrigin(mazeDisplayName_.getGlobalBounds().width/2.0f, mazeDisplayName_.getGlobalBounds().height/2.0f);
    mazeDisplayName_.setPosition(GAME_WIDTH/2.f, topLeft_.y/2.f);
    mazeDisplayName_.setFillColor(sf::Color(255,165,0));
    mazeDisplayName_.setScale(1.2,1.2);
}

void MazeSelectState::loadMazes(AssetManager& assetManager)
{
    assetManager.loadMazeList();
    mazeNames_ = assetManager.getMazeList();

    mazeIt = mazeNames_.begin();

    loadMazeData(game_->assetManager);
}

void MazeSelectState::nextMaze()
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

    loadMazeData(game_->assetManager);
}

void MazeSelectState::previousMaze()
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

    loadMazeData(game_->assetManager);
}

void MazeSelectState::loadMazeData(AssetManager& assetManager)
{
    currentMaze_ = *mazeIt;

    assetManager.loadLayout("current layout", currentMaze_);
    layout_ = assetManager.getLayout("current layout");

    assetManager.loadRotationMap("current rotation", currentMaze_);
    rotationMap_ = assetManager.getRotationMap("current rotation");
    
    assetManager.loadStartPos("current starts", currentMaze_);
    startPos_ = assetManager.getStartPos("current starts");

    mazeDisplayName_.setString(currentMaze_);
    mazeDisplayName_.setOrigin(mazeDisplayName_.getGlobalBounds().width/2.0f, mazeDisplayName_.getGlobalBounds().height/2.0f);
    mazeDisplayName_.setPosition(GAME_WIDTH/2.f, topLeft_.y/2.f);
}

void MazeSelectState::loadCharacters(AssetManager& assetManager)
{
    sf::Sprite sprite;
    
    sprite = sf::Sprite{*assetManager.getTexture("harambe head")};
    sprite.setOrigin(sprite.getGlobalBounds().width/2.f, sprite.getGlobalBounds().height/2.f);
    sprite.setScale(1.5f, 1.5f);
    characters_.push_back(sprite);
    
    auto textureString = vector<string>
    {
        "red head",
        "purple head",
        "green head",
        "brown head"
    };

    for (auto i = 0; i < textureString.size(); i++)
    {
        sprite = sf::Sprite{*assetManager.getTexture(textureString[i])};
        sprite.setOrigin(sprite.getGlobalBounds().width/2.f, sprite.getGlobalBounds().height/2.f);
        sprite.setScale(4.f/3.f, 4.f/3.f);
        characters_.push_back(sprite);
    }
}

void MazeSelectState::drawMaze()
{
    auto& assetManager = game_->assetManager;
    
    assetManager.loadTexture("grass", "resources/graphics/grass.png");
    bgTexture_ = *assetManager.getTexture("grass");
    bgTexture_.setRepeated(true);
    background_.setTexture(bgTexture_);
    background_.setPosition(topLeft_);
    background_.setTextureRect(sf::IntRect(topLeft_.x, topLeft_.y, NUM_COLS*tileLength_ - 25, NUM_ROWS*tileLength_ - 25));
    
    game_->window.draw(background_);
    
    sf::Sprite tile;
    
    vector<sf::Sprite> walls;
    
    for (auto row = 0; row < layout_.size(); row++)
    {
        for (auto col = 0; col < layout_[row].size(); col++)
        {
            tile = char2Sprite(layout_[row].at(col));
            tile.setPosition(topLeft_.x + col * tileLength_, topLeft_.y + row * tileLength_);
            tile.setRotation(char2Angle(rotationMap_[row].at(col)));
            
            if (layout_[row].at(col) == 'W' || layout_[row].at(col) == 'C')
                walls.push_back(tile);
            else
                game_->window.draw(tile);
        }
    }
    
    // Draw walls last
    for (auto& wall : walls)
        game_->window.draw(wall);
    
    // Draw characters
    characters_[0].setPosition(topLeft_ + tileLength_*startPos_[0]);
    characters_[1].setPosition(topLeft_ + tileLength_*startPos_[1]);
    characters_[2].setPosition(topLeft_ + tileLength_*startPos_[2]);
    characters_[3].setPosition(topLeft_ + tileLength_*startPos_[3]);
    characters_[4].setPosition(topLeft_ + tileLength_*startPos_[4]);
    
    for (auto& character : characters_)
        game_->window.draw(character);
}


sf::Sprite MazeSelectState::char2Sprite(char c)
{
    sf::Sprite sprite;

    switch (c)
    {
        case 'E':
            sprite.setTexture(*game_->assetManager.getTexture("empty"));
            break;
        case 'W':
            sprite.setTexture(*game_->assetManager.getTexture("wall"));
            break;
        case 'C':
            sprite.setTexture(*game_->assetManager.getTexture("corner"));
            break;
        case 'G':
            sprite.setTexture(*game_->assetManager.getTexture("gate"));
            break;
        case 'K':
            sprite.setTexture(*game_->assetManager.getTexture("key"));
            break;
        case 'F':
            sprite.setTexture(*game_->assetManager.getTexture("fruit"));
            break;
        case 'P':
            sprite.setTexture(*game_->assetManager.getTexture("power pellet"));
            break;
        case 'S':
            sprite.setTexture(*game_->assetManager.getTexture("super pellet"));
            break;

        default:
            sprite.setTexture(*game_->assetManager.getTexture("empty"));
            break;
    }

    sprite.setOrigin(sprite.getGlobalBounds().width/2.f, sprite.getGlobalBounds().height/2.f);
    sprite.setScale(14.f/17.f,14.f/17.f);

    return sprite;
}

float MazeSelectState::char2Angle(char c)
{
    switch (c)
    {
        case '0':
            return 0.f;
        case '1':
            return 90.f;
        case '2':
            return 180.f;
        case '3':
            return 270.f;

        default:
            return 0.f;
            break;
    }
}

void MazeSelectState::deleteMaze()
{
    if (mazeIt != mazeNames_.begin())
    {
        game_->assetManager.deleteMazeData(currentMaze_);
        
        auto temp = mazeIt - mazeNames_.begin();
        
        game_->assetManager.playSound("button click");
        
        game_->assetManager.loadMazeList();
        mazeNames_ = game_->assetManager.getMazeList();

        mazeIt = mazeNames_.begin();
        
        mazeIt += temp - 1;

        loadMazeData(game_->assetManager);
        
        return;
    }
    
    game_->assetManager.playSound("error");
}
