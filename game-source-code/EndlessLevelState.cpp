#include "EndlessLevelState.h"

#include "MainMenuState.h"  // Temp
//#include "WinningState.h"  // Temp
#include "IntermediateState.h"

#include "Configuration.h"
#include "DefaultCharacterState.h"
#include "GameOverState.h"
#include <iostream>
#include <utility>

EndlessLevelState::EndlessLevelState(gamePtr game, string mazeName, int lvlNumber): game_{game}, mazeName_{mazeName}, lvlNumber_{lvlNumber}
{
    // error checking
}

void EndlessLevelState::initialise()
{
    loadMaze(game_->assetManager);
    loadCharacters(game_->assetManager);
    loadInfoBar(game_->assetManager);
}

void EndlessLevelState::processInput()
{
    sf::Event event;

    while (game_->window.pollEvent(event))
    {
       if (game_->inputManager.isExitRequest(event))
            game_->window.close();
        
        if (event.type == sf::Event::Resized)
            game_->view = game_->inputManager.getLetterboxView(game_->view, event.size.width, event.size.height);

       if (event.type == sf::Event::KeyPressed)
       {
            switch (event.key.code)
            {
            case sf::Keyboard::Right:
                player_.Right();
                break;
            case sf::Keyboard::Left:
                player_.Left();
                break;
            case sf::Keyboard::Up:
                player_.Up();
                 break;
            case sf::Keyboard::Down:
                player_.Down();
                break;
            case sf::Keyboard::O:
                if (player_.livesLeft() > 1)
                    soundBoard_.prevSong();
                break;

            case sf::Keyboard::P:
                if (player_.livesLeft() > 1)
                    soundBoard_.nextSong();
                break;

            default:
                break;
            }
        }
    }
}

void EndlessLevelState::update(float dt)
{
    if (player_.livesLeft() > 1)
    {
        soundBoard_.checkSong();
    }

    updateInfoBar();

    player_.update(dt);
    blinky_.update(dt);
    pinky_.update(dt);
    inky_.update(dt);
    clyde_.update(dt);

    maze_.update();

    auto playerTile = maze_.getTile(player_.getSprite().getPosition());

    PlayerEnemyInteraction(blinky_);
    PlayerEnemyInteraction(inky_);
    PlayerEnemyInteraction(pinky_);
    PlayerEnemyInteraction(clyde_);

    if (player_.livesLeft() == 0)
    {
        scoreBoard_.endGame();

        soundBoard_.gameOver();

        game_->stateMachine.addState(make_unique<GameOverState>(game_, mazeName_, lvlNumber_));
    }

    playerTile->activate();
    //maze_.activate(playerTile);

    if (maze_.isClear())
    {
        scoreBoard_.endGame();

        soundBoard_.nextLevel();

        lvlNumber_++;
        game_->stateMachine.addState(make_unique<IntermediateState>(game_,mazeName_,lvlNumber_));
    }

}

void EndlessLevelState::draw(float dt)
{
    game_->window.clear(sf::Color{20,25,27});
    game_->window.setView(game_->view);
    
    game_->window.draw(background_);
    game_->window.draw(maze_);
    game_->window.draw(player_.getSprite());
    game_->window.draw(blinky_.getSprite());
    game_->window.draw(pinky_.getSprite());
    game_->window.draw(inky_.getSprite());
    game_->window.draw(clyde_.getSprite());

    game_->window.draw(scoreText_);
    for (auto life : livesCounter_)
        game_->window.draw(life);
    game_->window.draw(mazeHeading_);

    game_->window.display();
}

/*------------- Private helper functions -------------*/

void EndlessLevelState::loadMaze(AssetManager& assetManager)
{
    // Maze data elements
    assetManager.loadLayout("classic layout", mazeName_);
    assetManager.loadRotationMap("classic rotation", mazeName_);
    assetManager.loadKeyMap("classic key map", mazeName_);
    assetManager.loadStartPos("classic startPos", mazeName_);

    Maze::Data mazeData;

    mazeData.layout = assetManager.getLayout("classic layout");
    mazeData.rotationMap = assetManager.getRotationMap("classic rotation");
    mazeData.keyMap = assetManager.getKeyMap("classic key map");
    mazeData.startPos = assetManager.getStartPos("classic startPos");

    Maze::Textures mazeTextures;

    mazeTextures.empty = assetManager.getTexture("empty");
    mazeTextures.wall = assetManager.getTexture("wall");
    mazeTextures.corner = assetManager.getTexture("corner");
    mazeTextures.gate = assetManager.getTexture("gate");
    mazeTextures.brokenGate = assetManager.getTexture("broken gate");
    mazeTextures.key = assetManager.getTexture("key");
    mazeTextures.fruit = assetManager.getTexture("fruit");
    mazeTextures.powerPellet = assetManager.getTexture("power pellet");
    mazeTextures.superPellet = assetManager.getTexture("super pellet");

    Maze::Observers mazeObservers;

    mazeObservers.player = &player_;
    mazeObservers.enemies.push_back(&blinky_);
    mazeObservers.enemies.push_back(&inky_);
    mazeObservers.enemies.push_back(&pinky_);
    mazeObservers.enemies.push_back(&clyde_);

    mazeObservers.scoreBoard = &scoreBoard_;

    mazeObservers.soundBoard = &soundBoard_;

    maze_ = Maze{mazeData, mazeTextures, mazeObservers, sf::Vector2f{23,50}, TILE_LENGTH};//GAME_HEIGHT / mazeData.layout.size()};

    nodes_ = maze_.getNodes();
}

void EndlessLevelState::loadCharacters(AssetManager& assetManager)
{
    auto player_sprites = map<string,texturePtr>{};

    player_sprites["left"] = assetManager.getTexture("left");
    player_sprites["super left"] = assetManager.getTexture("super left");
    player_sprites["hit left"] = assetManager.getTexture("hit left");
    player_sprites["right"] = assetManager.getTexture("right");
    player_sprites["super right"] = assetManager.getTexture("super right");
    player_sprites["hit right"] = assetManager.getTexture("hit right");
    player_sprites["up"] = assetManager.getTexture("up");
    player_sprites["super up"] = assetManager.getTexture("super up");
    player_sprites["hit up"] = assetManager.getTexture("hit up");
    player_sprites["down"] = assetManager.getTexture("down");
    player_sprites["super down"] = assetManager.getTexture("super down");
    player_sprites["hit down"] = assetManager.getTexture("hit down");

    player_sprites["kill left"] = assetManager.getTexture("kill left");
    player_sprites["kill super left"] = assetManager.getTexture("kill super left");
    player_sprites["kill right"] = assetManager.getTexture("kill right");
    player_sprites["kill super right"] = assetManager.getTexture("kill super right");
    player_sprites["kill up"] = assetManager.getTexture("kill up");
    player_sprites["kill super up"] = assetManager.getTexture("kill super up");
    player_sprites["kill down"] = assetManager.getTexture("kill down");
    player_sprites["kill super down"] = assetManager.getTexture("kill super down");

    player_sprites["kill hit left"] = assetManager.getTexture("hit left");
    player_sprites["kill hit right"] = assetManager.getTexture("hit right");
    player_sprites["kill hit up"] = assetManager.getTexture("hit up");
    player_sprites["kill hit down"] = assetManager.getTexture("hit down");

    player_sprites["hit super left"] = assetManager.getTexture("hit super left");
    player_sprites["hit super right"] = assetManager.getTexture("hit super right");
    player_sprites["hit super up"] = assetManager.getTexture("hit super up");
    player_sprites["hit super down"] = assetManager.getTexture("hit super down");

    player_sprites["kill hit super left"] = assetManager.getTexture("hit super left");
    player_sprites["kill hit super right"] = assetManager.getTexture("hit super right");
    player_sprites["kill hit super up"] = assetManager.getTexture("hit super up");
    player_sprites["kill hit super down"] = assetManager.getTexture("hit super down");

    player_sprites["dead"] = assetManager.getTexture("harambe dead");

    player_ = Player{player_sprites, maze_.getPlayerStart(), &maze_};

    auto enemy_sprites = map<string,texturePtr>{};

    enemy_sprites["frightened"] = assetManager.getTexture("blue police");
    enemy_sprites["dead"] = assetManager.getTexture("police dead");

    enemy_sprites["default"] = assetManager.getTexture("red police");
    blinky_ = Blinky{enemy_sprites, maze_.getEnemyStarts()[0], &player_, &maze_};

    enemy_sprites["default"] = assetManager.getTexture("purple police");
    pinky_ = Pinky{enemy_sprites, maze_.getEnemyStarts()[1], &player_, &maze_};

    enemy_sprites["default"] = assetManager.getTexture("green police");
    inky_ = Inky{enemy_sprites, maze_.getEnemyStarts()[2], &player_, &maze_, &blinky_};

    enemy_sprites["default"] = assetManager.getTexture("brown police");
    clyde_ = Clyde{enemy_sprites, maze_.getEnemyStarts()[3], &player_, &maze_};

    Character::setLevelNumber(lvlNumber_);

    blinky_.addObserver(&scoreBoard_);
    pinky_.addObserver(&scoreBoard_);
    inky_.addObserver(&scoreBoard_);
    clyde_.addObserver(&scoreBoard_);
    blinky_.addObserver(&player_);
    pinky_.addObserver(&player_);
    inky_.addObserver(&player_);
    clyde_.addObserver(&player_);

    blinky_.addObserver(&soundBoard_);
    pinky_.addObserver(&soundBoard_);
    inky_.addObserver(&soundBoard_);
    clyde_.addObserver(&soundBoard_);

    player_.addObserver(&soundBoard_);

    life_.setTexture(*assetManager.getTexture("harambe head"));
    life_.setOrigin(assetManager.getTexture("harambe head")->getSize().x /2, assetManager.getTexture("harambe head")->getSize().y /2);
    life_.setScale(1.9,1.9);
}

void EndlessLevelState::loadInfoBar(AssetManager& assetManager)
{
    assetManager.loadHighScores(mazeName_);

    auto highscores = assetManager.getHighScores();

    scoreBoard_ = Scoreboard{highscores};

    scoreText_.setFont(*assetManager.getFont("fine 8-bit"));
    scoreText_.setOrigin(scoreText_.getGlobalBounds().left, scoreText_.getGlobalBounds().height/2.0f);
    scoreText_.setPosition(get<0>(maze_.getMazeBounds()).x + 10, 20);

    mazeHeading_.setFont(*assetManager.getFont("fine 8-bit"));
    mazeHeading_.setString(mazeName_);
    mazeHeading_.setOrigin(mazeHeading_.getGlobalBounds().width/2.0f, mazeHeading_.getGlobalBounds().height/2.0f);
    mazeHeading_.setPosition(get<0>(maze_.getMazeBounds()).x + maze_.getWidth()/2, 25);
    mazeHeading_.setFillColor(sf::Color(255,165,0));
    mazeHeading_.setOutlineColor(sf::Color::Black);
    mazeHeading_.setOutlineThickness(2.f);
    mazeHeading_.setScale(1.2,1.2);

    bgTexture_ = *assetManager.getTexture("grass");
    bgTexture_.setRepeated(true);
    background_.setTexture(bgTexture_);
    background_.setPosition(get<0>(maze_.getMazeBounds())+sf::Vector2f{10,10});
    background_.setTextureRect(sf::IntRect(get<0>(maze_.getMazeBounds()).x, get<0>(maze_.getMazeBounds()).y, maze_.getWidth()-20, maze_.getHeight()-20));

    soundBoard_ = Soundboard(game_);

}

void EndlessLevelState::PlayerEnemyInteraction(Enemy& enemy)
{
     auto enemyTile = enemy.getCurrentTile();
     auto playerTile = player_.getCurrentTile();

     if (!(playerTile == enemyTile))
        return;

     if (!player_.isInteractive())
        return;

     if (!enemy.isInteractive())
        return;

    if (enemy.isFrightened())
    {
        player_.eat();
        enemy.die();
    }
    else if (!player_.isSuper())
    {
        player_.die();
        resetCharacters();
        if (player_.livesLeft() == 1)
            soundBoard_.lastLife();
    }
}

void EndlessLevelState::resetCharacters()
{
    blinky_.PlayerDead();
    clyde_.PlayerDead();
    inky_.PlayerDead();
    pinky_.PlayerDead();
}

void EndlessLevelState::updateInfoBar()
{
    scoreText_.setString("SCORE " + to_string(scoreBoard_.getCurrentScore()));
    scoreText_.setFillColor(sf::Color(137,207,240));
    scoreText_.setOutlineColor(sf::Color::Black);
    scoreText_.setOutlineThickness(2.f);

    livesCounter_.clear();
    for (int l = 0; l<player_.livesLeft(); l++)
    {
        livesCounter_.push_back(life_);
        livesCounter_[l].setPosition(sf::Vector2f{get<1>(maze_.getMazeBounds()).x-(l+1)*37,40});
    }

}
