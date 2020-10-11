#include "SplashState.h"
#include "MainMenuState.h"

#include "Configuration.h"
#include "Soundboard.h"

#include <cmath>
#include <iostream>

SplashState::SplashState(gamePtr game): game_{game}
{
    // error checking
}

void SplashState::initialise()  // I wonder if we should load EVERYTHING here so that access is easier later?
{
    // Loading all resources up front
    loadSounds(game_->assetManager);
    loadFonts(game_->assetManager);
    loadTextures(game_->assetManager);

    loadBackground(game_->assetManager);
    loadPercentage(game_->assetManager);
    loadProgressBar();
}

void SplashState::processInput()
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

void SplashState::update(float dt)
{
    float elapsedTime = clock_.getElapsedTime().asSeconds();

    if (elapsedTime > SPLASH_DISPLAY_TIME)
    {
        game_->stateMachine.addState(make_unique<MainMenuState>(game_));
    }
    else
    {
        progress_ = elapsedTime/SPLASH_DISPLAY_TIME;
        bar_.setSize(sf::Vector2f{PROGRESS_BAR_WIDTH * progress_, PROGRESS_BAR_HEIGHT});
        percentage_.setString(to_string(static_cast<int>(progress_ * 100) + 1) + "%");
    }

}

void SplashState::draw(float dt)
{
    game_->window.clear();
    game_->window.setView(game_->view);

    game_->window.draw(background_);
    game_->window.draw(title_);
    game_->window.draw(percentage_);
    game_->window.draw(bar_);
    game_->window.draw(barOutline_);

    game_->window.display();
}

/*------------- Private helper functions -------------*/

void SplashState::loadSounds(AssetManager& assetManager)
{
    // SFX
    assetManager.loadSoundBuffer("button click", BUTTON_SFX1_FILEPATH);
    assetManager.loadSoundBuffer("select button", SELECT_BUTTON_SFX1_FILEPATH);
    assetManager.loadSoundBuffer("key", KEY_SFX_FILEPATH);
    assetManager.loadSoundBuffer("gate link", GATE_LINK_SFX_FILEPATH);
    assetManager.loadSoundBuffer("super pellet", SUPER_PELLET_SFX_FILEPATH);
    assetManager.loadSoundBuffer("power pellet", POWER_PELLET_SFX_FILEPATH);
    assetManager.loadSoundBuffer("gate break", GATE_BREAK_SFX_FILEPATH);
    assetManager.loadSoundBuffer("player die", PLAYER_DIE_SFX_FILEPATH);
    assetManager.loadSoundBuffer("eat ghost", EAT_GHOST_SFX_FILEPATH);
    assetManager.loadSoundBuffer("error", ERROR_BUTTON_SFX_FILEPATH);

    // Songs
    assetManager.loadMusic("coffin dance", COFFIN_DANCE_FILEPATH);
    assetManager.loadMusic("unravel", UNRAVEL_FILEPATH);
    assetManager.loadMusic("xue hua piao", XUE_HUA_PIAO_FILEPATH);
    assetManager.loadMusic("giorno", GIORNO_FILEPATH);
    assetManager.loadMusic("caramelldansen", CARAMELLDANSEN_FILEPATH);
    assetManager.loadMusic("megalovania", MEGALOVANIA_FILEPATH);
    assetManager.loadMusic("full metal", FULL_METAL_FILEPATH);
    assetManager.loadMusic("crab rave", CRAB_RAVE_FILEPATH);
    assetManager.loadMusic("deja vu", DEJA_VU_FILEPATH);
    assetManager.loadMusic("running in 90s", RUNNING_IN_90S_FILEPATH);
    assetManager.loadMusic("rick roll", RICK_ROLL_FILEPATH);
    assetManager.loadMusic("levan polka", LEVAN_POLKA_FILEPATH);
    assetManager.loadMusic("damaged coda", DAMAGED_CODA_FILEPATH);
    assetManager.loadMusic("sandstorm", SANDSTORM_FILEPATH);
    Soundboard::seedRandom();
}

void SplashState::loadFonts(AssetManager& assetManager)
{
    assetManager.loadFont("fine 8-bit", FINE_8_BIT_FONT_FILEPATH);
    assetManager.loadFont("coarse 8-bit", COARSE_8_BIT_FONT_FILEPATH);
    assetManager.loadFont("pressStart 8-bit", PRESS_START_8_BIT_FONT_FILEPATH);
    assetManager.loadFont("ancient", ANCIENT_8_BIT_FONT_FILEPATH);
}

void SplashState::loadTextures(AssetManager& assetManager)
{
    assetManager.loadTexture("splash background", SPLASH_BACKGROUND_FILEPATH);
    assetManager.loadTexture("menu background", MENU_BACKGROUND_FILEPATH);
    assetManager.loadTexture("aux background", AUX_BACKGROUND_FILEPATH);
    assetManager.loadTexture("hs background", HS_BACKGROUND_FILEPATH);
    assetManager.loadTexture("grass", GRASS_FILEPATH);

    // Buttons
    assetManager.loadTexture("menu button", MENU_BUTTON_FILEPATH);
    assetManager.loadTexture("exit button", EXIT_BUTTON_FILEPATH);
    assetManager.loadTexture("eraser", ERASE_BUTTON_FILEPATH);
    assetManager.loadTexture("left triangle", LEFT_TRIANGLE_FILEPATH);
    assetManager.loadTexture("right triangle", RIGHT_TRIANGLE_FILEPATH);
    assetManager.loadTexture("blank-button", BLANK_BUTTON_FILEPATH);
    assetManager.loadTexture("question mark", QUESTION_MARK_FILEPATH);

    assetManager.loadTexture("player default", PLAYER_DEFAULT_FILEPATH); // delete these?
    assetManager.loadTexture("player super", PLAYER_SUPER_FILEPATH);
    assetManager.loadTexture("enemy default", ENEMY_DEFAULT_FILEPATH);

    // Maze textures
    assetManager.loadTexture("empty", EMPTY_FILEPATH);
    assetManager.loadTexture("wall", WALL_FILEPATH);
    assetManager.loadTexture("corner", CORNER_FILEPATH);
    assetManager.loadTexture("gate", GATE_FILEPATH);
    assetManager.loadTexture("broken gate", BROKEN_GATE_FILEPATH);
    assetManager.loadTexture("key", KEY_FILEPATH);
    assetManager.loadTexture("fruit", BANANA_FILEPATH);
    assetManager.loadTexture("power pellet", POWER_PELLET_FILEPATH);
    assetManager.loadTexture("super pellet", SUPER_PELLET_FILEPATH);

    // Player textures
    assetManager.loadTexture("left", HARAMBE_LEFT);
    assetManager.loadTexture("right", HARAMBE_RIGHT);
    assetManager.loadTexture("up", HARAMBE_UP);
    assetManager.loadTexture("down", HARAMBE_DOWN);

    assetManager.loadTexture("super left", SUPER_HARAMBE_LEFT);
    assetManager.loadTexture("super right", SUPER_HARAMBE_RIGHT);
    assetManager.loadTexture("super up", SUPER_HARAMBE_UP);
    assetManager.loadTexture("super down", SUPER_HARAMBE_DOWN);

    assetManager.loadTexture("kill left", KILL_HARAMBE_LEFT);
    assetManager.loadTexture("kill right", KILL_HARAMBE_RIGHT);
    assetManager.loadTexture("kill up", KILL_HARAMBE_UP);
    assetManager.loadTexture("kill down", KILL_HARAMBE_DOWN);

    assetManager.loadTexture("kill super left", KILL_SUPER_HARAMBE_LEFT);
    assetManager.loadTexture("kill super right", KILL_SUPER_HARAMBE_RIGHT);
    assetManager.loadTexture("kill super up", KILL_SUPER_HARAMBE_UP);
    assetManager.loadTexture("kill super down", KILL_SUPER_HARAMBE_DOWN);

    assetManager.loadTexture("hit left", HIT_HARAMBE_LEFT);
    assetManager.loadTexture("hit right", HIT_HARAMBE_RIGHT);
    assetManager.loadTexture("hit up", HIT_HARAMBE_UP);
    assetManager.loadTexture("hit down", HIT_HARAMBE_DOWN);

    assetManager.loadTexture("hit super left", HIT_SUPER_HARAMBE_LEFT);
    assetManager.loadTexture("hit super right", HIT_SUPER_HARAMBE_RIGHT);
    assetManager.loadTexture("hit super up", HIT_SUPER_HARAMBE_UP);
    assetManager.loadTexture("hit super down", HIT_SUPER_HARAMBE_DOWN);

    assetManager.loadTexture("harambe dead", HARAMBE_DEAD);
    assetManager.loadTexture("harambe head", HARAMBE_HEAD );
    assetManager.loadTexture("red police", RED_POLICE);
    assetManager.loadTexture("green police", GREEN_POLICE);
    assetManager.loadTexture("brown police", BROWN_POLICE);
    assetManager.loadTexture("purple police", PURPLE_POLICE);
    assetManager.loadTexture("blue police", BLUE_POLICE);

    assetManager.loadTexture("police dead", POLICE_DEAD);

    assetManager.loadTexture("red head", RED_HEAD);
    assetManager.loadTexture("green head", GREEN_HEAD);
    assetManager.loadTexture("purple head", PURPLE_HEAD);
    assetManager.loadTexture("brown head", BROWN_HEAD);

    // Coffin textures
    assetManager.loadTexture("coffin0", COFFIN_1);
    assetManager.loadTexture("coffin1", COFFIN_2);
    assetManager.loadTexture("coffin2", COFFIN_3);
    assetManager.loadTexture("coffin3", COFFIN_4);
    assetManager.loadTexture("coffin4", COFFIN_5);
    assetManager.loadTexture("coffin5", COFFIN_6);
    assetManager.loadTexture("coffin6", COFFIN_7);
    assetManager.loadTexture("coffin7", COFFIN_8);

    // Piao Piao
    assetManager.loadTexture("petal0", PETALS_1);
    assetManager.loadTexture("petal1", PETALS_2);
    assetManager.loadTexture("petal2", PETALS_3);
    assetManager.loadTexture("petal3", PETALS_4);
    assetManager.loadTexture("petal4", PETALS_5);
    assetManager.loadTexture("petal5", PETALS_6);
    assetManager.loadTexture("petal6", PETALS_7);
    assetManager.loadTexture("petal7", PETALS_8);
    assetManager.loadTexture("petal8", PETALS_9);
    assetManager.loadTexture("petal9", PETALS_10);
    assetManager.loadTexture("petal10", PETALS_11);

    assetManager.loadTexture("sakura tree", SAKURA_TREE);
    assetManager.loadTexture("piao piao", PIAO_PIAO);

}

void SplashState::loadBackground(AssetManager& assetManager)
{
    background_.setTexture(*assetManager.getTexture("splash background"));
}

void SplashState::loadPercentage(AssetManager& assetManager)
{
    percentage_.setFont(*assetManager.getFont("fine 8-bit"));

    percentage_.setString("00%");
    percentage_.setOrigin(percentage_.getGlobalBounds().width/2.0f,
                          percentage_.getGlobalBounds().height/2.0f);
    percentage_.setPosition(PERCENTAGE_POSITION);
    percentage_.setFillColor(PROGRESS_BAR_COLOUR);
}

void SplashState::loadProgressBar()
{
    bar_.setPosition(PROGRESS_BAR_POSITION);
    bar_.setFillColor(PROGRESS_BAR_COLOUR);

    barOutline_.setSize(sf::Vector2f{PROGRESS_BAR_OUTLINE_WIDTH, PROGRESS_BAR_OUTLINE_HEIGHT});
    barOutline_.setOrigin(barOutline_.getGlobalBounds().width/2.0f,
                          barOutline_.getGlobalBounds().height/2.0f);
    barOutline_.setOutlineThickness(PROGRESS_BAR_OUTLINE_THICKNESS);
    barOutline_.setPosition(PROGRESS_BAR_OUTLINE_POSITION);
    barOutline_.setFillColor(sf::Color::Transparent);
    barOutline_.setOutlineColor(PROGRESS_BAR_COLOUR);
}

