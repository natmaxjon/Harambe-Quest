#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../game-source-code/Configuration.h"

#include "../game-source-code/EmptyTile.h"
#include "../game-source-code/WallTile.h"
#include "../game-source-code/GateTile.h"
#include "../game-source-code/KeyTile.h"
#include "../game-source-code/FruitTile.h"
#include "../game-source-code/SuperTile.h"
#include "../game-source-code/PowerTile.h"

#include "../game-source-code/Maze.h"
#include "../game-source-code/FileReader.h"
#include "../game-source-code/AssetManager.h"

#include "../game-source-code/Player.h"
#include "../game-source-code/Blinky.h"
#include "../game-source-code/Pinky.h"
#include "../game-source-code/Inky.h"
#include "../game-source-code/Clyde.h"

#include <string>
#include <iostream>
#include <vector>
#include <memory>


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;

typedef shared_ptr<Tile> tilePtr;
typedef shared_ptr<sf::Texture> texturePtr;
//Helper functions

Maze initializeMaze(){

    auto assetManager = AssetManager{};

    auto mazeName_ = "Classic"s;
    assetManager.loadLayout("classic layout", mazeName_);
    assetManager.loadRotationMap("classic rotation", mazeName_);
    assetManager.loadKeyMap("classic key map", mazeName_);
    assetManager.loadStartPos("classic startPos", mazeName_);

    Maze::Data mazeData;

    mazeData.layout = assetManager.getLayout("classic layout");
    mazeData.rotationMap = assetManager.getRotationMap("classic rotation");
    mazeData.keyMap = assetManager.getKeyMap("classic key map");
    mazeData.startPos = assetManager.getStartPos("classic startPos");

    // Maze Texture elements
    assetManager.loadTexture("wall", WALL_FILEPATH);
    assetManager.loadTexture("corner", CORNER_FILEPATH);
    assetManager.loadTexture("gate", GATE_FILEPATH);
    assetManager.loadTexture("broken gate", BROKEN_GATE_FILEPATH);
    assetManager.loadTexture("key", KEY_FILEPATH);
    assetManager.loadTexture("banana", BANANA_FILEPATH);
    assetManager.loadTexture("power pellet", POWER_PELLET_FILEPATH);
    assetManager.loadTexture("super pellet", SUPER_PELLET_FILEPATH);
    assetManager.loadTexture("empty", EMPTY_FILEPATH);

    Maze::Textures mazeTextures;

    mazeTextures.empty = assetManager.getTexture("empty");
    mazeTextures.wall = assetManager.getTexture("wall");
    mazeTextures.corner = assetManager.getTexture("corner");
    mazeTextures.gate = assetManager.getTexture("gate");
    mazeTextures.brokenGate = assetManager.getTexture("broken gate");
    mazeTextures.key = assetManager.getTexture("key");
    mazeTextures.fruit = assetManager.getTexture("banana");
    mazeTextures.powerPellet = assetManager.getTexture("power pellet");
    mazeTextures.superPellet = assetManager.getTexture("super pellet");

    Maze::Observers mazeObservers;

    mazeObservers.player = {};
    mazeObservers.enemies = {};

    auto tileLength = 36.0f;

    return Maze{mazeData, mazeTextures, mazeObservers, sf::Vector2f{0,0}, tileLength};

}

void collisions(Player& player, Enemy& enemy)
{
     auto enemyTile = enemy.getCurrentTile();
     auto playerTile = player.getCurrentTile();

     if (!(playerTile == enemyTile))
        return;

     if (!player.isInteractive())
        return;

     if (!enemy.isInteractive())
        return;

    if (enemy.isFrightened())
    {
        player.eat();
        enemy.die();
    }
    else if (!player.isSuper())
    {
        player.die();
    }
}


void loadPlayerAssets(map<string,texturePtr>& player_sprites)
{
    auto assetManager = AssetManager{};

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

    assetManager.loadTexture("harambe dead", HARAMBE_DEAD);

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

    player_sprites["dead"] = assetManager.getTexture("harambe dead");
}

void loadEnemyAssets(map<string,texturePtr>& enemy_sprites)
{
    auto assetManager = AssetManager{};

    assetManager.loadTexture("purple police", PURPLE_POLICE);
    assetManager.loadTexture("blue police", BLUE_POLICE);
    assetManager.loadTexture("police dead", POLICE_DEAD);

    enemy_sprites["frightened"] = assetManager.getTexture("blue police");
    enemy_sprites["dead"] = assetManager.getTexture("police dead");
    enemy_sprites["default"] = assetManager.getTexture("purple police");
}




// ------------- Tests for Tiles ----------------

TEST_CASE("Tile constructor correctly initialises relevant data members")
{
    auto position = sf::Vector2f{20,30};
    auto angle = 45.f;

    auto texture = make_shared<sf::Texture>();
    texture->loadFromFile(EMPTY_FILEPATH);

    auto sprite = sf::Sprite{*texture};
    sprite.setOrigin(sprite.getGlobalBounds().width/2.f,
                     sprite.getGlobalBounds().height/2.f);
    sprite.setPosition(position.x, position.y);
    sprite.setRotation(angle);

    auto tile = EmptyTile{position, angle, texture};

    CHECK(tile.getPosition() == position);
    CHECK(tile.getAngle() == angle);
    CHECK(tile.getSprite().getGlobalBounds()  == sprite.getGlobalBounds());
}

TEST_CASE("Sprite can be correctly set after initialisation")
{
    auto texture = make_shared<sf::Texture>();
    texture->loadFromFile(EMPTY_FILEPATH);
    auto sprite = sf::Sprite{*texture};

    auto tile = EmptyTile{};

    tile.setSprite(sprite);

    CHECK(tile.getSprite().getLocalBounds()  == sprite.getLocalBounds());
}

TEST_CASE("Tile can be correctly set for removal")
{
    auto tile = EmptyTile();

    CHECK_FALSE(tile.isRemoved());

    tile.remove();

    CHECK(tile.isRemoved());
}

TEST_CASE("All consumable tiles are set for removal when activated")
{
    auto key = KeyTile{};
    auto fruit = FruitTile{};
    auto powerPellet = PowerTile{};
    auto superPellet = SuperTile{};

    CHECK_FALSE(key.isRemoved());
    CHECK_FALSE(fruit.isRemoved());
    CHECK_FALSE(powerPellet.isRemoved());
    CHECK_FALSE(superPellet.isRemoved());

    key.activate();
    fruit.activate();
    powerPellet.activate();
    superPellet.activate();

    CHECK(key.isRemoved());
    CHECK(fruit.isRemoved());
    CHECK(powerPellet.isRemoved());
    CHECK(superPellet.isRemoved());
}

TEST_CASE("All tile types can correctly identify whether they are a node")
{
    auto empty = EmptyTile{};
    auto wall = WallTile{};
    auto gate = GateTile{};
    auto key = KeyTile{};
    auto fruit = FruitTile{};
    auto powerPellet = PowerTile{};
    auto superPellet = SuperTile{};

    CHECK(empty.isNode());
    CHECK_FALSE(wall.isNode());
    CHECK_FALSE(gate.isNode());
    CHECK(key.isNode());
    CHECK(fruit.isNode());
    CHECK(powerPellet.isNode());
    CHECK(superPellet.isNode());
}

TEST_CASE("Gate tiles can be made into nodes statically")
{
    auto gate = GateTile{};

    CHECK_FALSE(gate.isNode());

    GateTile::isNode(true);

    CHECK(gate.isNode());

    GateTile::isNode(false);
}

TEST_CASE("Gate tiles become nodes when activated")
{
    auto gate = GateTile{};

    CHECK_FALSE(gate.isNode());

    gate.activate();

    CHECK(gate.isNode());
}

TEST_CASE("Gate tiles change their sprite when activated")
{
    auto normalTexture = make_shared<sf::Texture>();
    normalTexture->loadFromFile(GATE_FILEPATH);
    auto normalSprite = sf::Sprite{*normalTexture};

    auto brokenTexture = make_shared<sf::Texture>();
    brokenTexture->loadFromFile(BROKEN_GATE_FILEPATH);
    auto brokenSprite = sf::Sprite{*brokenTexture};

    auto gate = GateTile{sf::Vector2f{0,0}, 0.f, normalTexture, brokenTexture};

    CHECK(gate.getSprite().getLocalBounds() == normalSprite.getLocalBounds());

    gate.activate();

    CHECK(gate.getSprite().getLocalBounds() == brokenSprite.getLocalBounds());
}

TEST_CASE("Key tiles set their corresponding gate tiles to be removed")
{
    auto texture = make_shared<sf::Texture>();
    texture->loadFromFile(KEY_FILEPATH);

    auto gates = vector<tilePtr>(3, make_shared<GateTile>());

    auto key = KeyTile{sf::Vector2f{0,0}, 0.f, texture, gates};

    CHECK_FALSE(gates[0]->isRemoved());
    CHECK_FALSE(gates[1]->isRemoved());
    CHECK_FALSE(gates[2]->isRemoved());

    key.activate();

    CHECK(gates[0]->isRemoved());
    CHECK(gates[1]->isRemoved());
    CHECK(gates[2]->isRemoved());
}

// ------------- Tests for Maze ----------------



// ------------- Tests for Characters ----------------


TEST_CASE("Player cannot move through walls")
{
    auto maze = initializeMaze();
    auto tileLength = maze.getTileLength();
    auto assetManager = AssetManager{};

    map<string,texturePtr> player_sprites;



//    for (auto row: maze.getMaze())
//    {
//        for (auto col : row)
//        {
//           cout <<  "(" << col->getPosition().x << ", " << col->getPosition().y << ") ";
//        }
//        cout << endl;
//    }

    auto player_start = sf::Vector2f{414,630};


    loadPlayerAssets(player_sprites);
    auto player = Player{player_sprites, player_start, &maze};


    //he travels a block with each update
    auto dt = tileLength/NORMAL_CHARACTER_SPEED;

    SUBCASE("Player follows the path until a wall"){
        player.Right();
        for (int i = 0; i<2; i++)
            player.update(dt);

        SUBCASE("Player follows the path"){
            auto new_pos = player_start + tileLength*sf::Vector2f{2,0};
            CHECK(player.getCurrentTile() == new_pos);
        }

        SUBCASE("Player stays stationary once he hits the wall"){
            for (int i = 0; i<2; i++)
                player.update(dt);

            auto new_pos = player_start + tileLength*sf::Vector2f{2,0};
            CHECK(player.getCurrentTile() == new_pos);
        }

        SUBCASE("If direction is changed, player moves again along the path"){
            player.Down();
            for (int i = 0; i<5; i++)
                player.update(dt);
            auto new_pos = player_start + tileLength*sf::Vector2f{2,4};
            CHECK(player.getCurrentTile() == new_pos);
        }

    }

    SUBCASE("Player turns only at the NEXT intersection"){
        player.Up();
        player.update(dt);
        player.Right();

        player.update(dt);
        player.update(dt);

        SUBCASE("Player continues to move up before the intersection"){
            auto new_pos = player_start + tileLength*sf::Vector2f{0,-3};
            CHECK(player.getCurrentTile() == new_pos);
        }

        for (int i = 0; i<5; i++)
            player.update(dt);

        SUBCASE("Player turns right at the intersection and continues to move"){
            auto new_pos = player_start + tileLength*sf::Vector2f{2,-6};
            CHECK(player.getCurrentTile() == new_pos);
        }


        SUBCASE("Player stops at the end of the path and does not enter any gates"){
        for (int i = 0; i<3; i++)
            player.update(dt);

            auto new_pos = player_start + tileLength*sf::Vector2f{4,-6};
            CHECK(player.getCurrentTile() == new_pos);
        }

    }

}

TEST_CASE("Player can reverse direction even before a node") {

    auto maze = initializeMaze();
    auto tileLength = maze.getTileLength();

    auto assetManager = AssetManager{};

    auto player_start = sf::Vector2f{414,630};

    map<string,texturePtr> player_sprites;
    loadPlayerAssets(player_sprites);
    auto player = Player{player_sprites, player_start, &maze};

    auto dt = tileLength/(2*NORMAL_CHARACTER_SPEED);

    player.Up();

    for (int i = 0; i<5; i++)
        player.update(dt);

    player.Down();
    player.update(dt);
    player.update(dt);

    auto new_pos = player_start + tileLength*sf::Vector2f{0,-1.5};
    CHECK(player.getSprite().getPosition() == new_pos);
}

TEST_CASE("Ghost moves intelligently towards Player using shortest route")
{

    auto maze = initializeMaze();
    auto tileLength = maze.getTileLength();

    auto assetManager = AssetManager{};

    auto player_start = sf::Vector2f{198,738};

    map<string,texturePtr> player_sprites;
    loadPlayerAssets(player_sprites);
    auto player = Player{player_sprites, player_start, &maze};

    auto dt = tileLength/NORMAL_ENEMY_SPEED;
    auto enemy_start = sf::Vector2f{54,594};

    map<string,texturePtr> enemy_sprites;
    loadEnemyAssets(enemy_sprites);
    auto blinky = Blinky{enemy_sprites, enemy_start, &player, &maze};
    // He will move up once
    blinky.update(dt);
    blinky.ChaseMode();
    blinky.update(dt);

    SUBCASE("Ghost turns at next intersection to minimise distance to target"){
        for (int i = 0; i<4; i++)
            blinky.update(dt);

        auto new_pos = enemy_start + tileLength*sf::Vector2f{1,3};
            CHECK(blinky.getSprite().getPosition() == new_pos);
    }

    SUBCASE("Ghost follows path to target's position"){
        for (int i = 0; i<8; i++)
        {
           blinky.update(dt);
        }


        CHECK(blinky.getSprite().getPosition() == player_start);
    }

}

TEST_CASE("Ghost do not turn around even if it is shorter to do so")
{

    auto maze = initializeMaze();
    auto tileLength = maze.getTileLength();

    auto assetManager = AssetManager{};

    auto player_start = sf::Vector2f{126,486};

    map<string,texturePtr> player_sprites;
    loadPlayerAssets(player_sprites);
    auto player = Player{player_sprites, player_start, &maze};

    auto dt = tileLength/NORMAL_ENEMY_SPEED;
    auto enemy_start = sf::Vector2f{54,558};
    map<string,texturePtr> enemy_sprites;
    loadEnemyAssets(enemy_sprites);
    auto blinky = Blinky{enemy_sprites, enemy_start, &player, &maze};

    blinky.update(dt);
    blinky.ChaseMode();
    blinky.update(dt);
    for (int i = 0; i<16; i++)
       blinky.update(dt);

    CHECK(blinky.getSprite().getPosition() == player_start);
}

TEST_CASE("Target tiles for Blinky are correct")
{
    auto maze = initializeMaze();
    auto tileLength = maze.getTileLength();

    auto assetManager = AssetManager{};
    auto player_start = sf::Vector2f{414,630};

    map<string,texturePtr> player_sprites;
    loadPlayerAssets(player_sprites);
    auto player = Player{player_sprites, player_start, &maze};

    auto dt = tileLength/NORMAL_ENEMY_SPEED;
    auto enemy_start = maze.getEnemyStarts()[0];

    map<string,texturePtr> enemy_sprites;
    loadEnemyAssets(enemy_sprites);
    auto blinky = Blinky{enemy_sprites, enemy_start, &player, &maze};

    blinky.update(dt);

    SUBCASE("Blinky's scatter target is the top left corner")
    {
        auto correct_target = sf::Vector2f{18,18};
        CHECK(blinky.getScatterTarget() == correct_target);
    }

    blinky.ChaseMode();
    blinky.update(dt);

    SUBCASE("Blinky's chase target is the player")
    {
        auto correct_target = player.getSprite().getPosition();
        CHECK(blinky.getChaseTarget() == correct_target);
    }
}

TEST_CASE("Target tiles for Pinky are correct")
{
    auto maze = initializeMaze();
    auto tileLength = maze.getTileLength();

    auto assetManager = AssetManager{};

    assetManager.loadTexture("player default", PLAYER_DEFAULT_FILEPATH);
    auto player_default = assetManager.getTexture("player default");
    auto player_start = sf::Vector2f{414,630};

    map<string,texturePtr> player_sprites;
    loadPlayerAssets(player_sprites);
    auto player = Player{player_sprites, player_start, &maze};

    auto dt = tileLength/NORMAL_ENEMY_SPEED;
    auto enemy_start = maze.getEnemyStarts()[1];


    map<string,texturePtr> enemy_sprites;
    loadEnemyAssets(enemy_sprites);
    auto pinky = Pinky{enemy_sprites, enemy_start, &player, &maze};

    pinky.update(dt);

    SUBCASE("Pinky's scatter target is the top right corner")
    {
        auto correct_target = sf::Vector2f{810,18};
        CHECK(pinky.getScatterTarget() == correct_target);
    }

    pinky.ChaseMode();
    pinky.update(dt);

    SUBCASE("Pinky's chase target is four tiles ahead of the player")
    {
        auto correct_target = player.getSprite().getPosition() + 4*tileLength*player.currentDir();
        CHECK(pinky.getChaseTarget() == correct_target);
    }
}

TEST_CASE("Target tiles for Inky are correct")
{
    auto maze = initializeMaze();
    auto tileLength = maze.getTileLength();

    auto assetManager = AssetManager{};

    auto player_start = sf::Vector2f{414,630};

    map<string,texturePtr> player_sprites;
    loadPlayerAssets(player_sprites);
    auto player = Player{player_sprites, player_start, &maze};

    auto dt = tileLength/NORMAL_ENEMY_SPEED;
    auto enemy_start = maze.getEnemyStarts()[2];
    auto blinky_start = maze.getEnemyStarts()[2];

    map<string,texturePtr> enemy_sprites;
    loadEnemyAssets(enemy_sprites);
    auto blinky = Blinky{enemy_sprites, enemy_start, &player, &maze};

    auto inky = Inky{enemy_sprites, enemy_start, &player, &maze, &blinky};

    inky.update(dt);

    SUBCASE("Inky's scatter target is the bottom left corner")
    {
        auto correct_target = sf::Vector2f{18,882};
        CHECK(inky.getScatterTarget() == correct_target);
    }

    inky.ChaseMode();
    inky.update(dt);

    SUBCASE("Inky's chase target is a 180 degree rotation of the vector between blinky and two tiles ahead of the player")
    {
        auto mid_target = player.getCurrentTile() + 2.0f*tileLength*player.currentDir();
        auto correct_target = 2.0f*mid_target - blinky.getCurrentTile();
        CHECK(inky.getChaseTarget() == correct_target);
    }
}


TEST_CASE("Target tiles for Clyde are correct")
{
    auto maze = initializeMaze();
    auto tileLength = maze.getTileLength();

    auto assetManager = AssetManager{};


    auto player_start = sf::Vector2f{414,630};

    map<string,texturePtr> player_sprites;
    loadPlayerAssets(player_sprites);
    auto player = Player{player_sprites, player_start, &maze};

    auto dt = tileLength/NORMAL_ENEMY_SPEED;
    auto enemy_start = maze.getEnemyStarts()[3];

    map<string,texturePtr> enemy_sprites;
    loadEnemyAssets(enemy_sprites);
    auto clyde= Clyde{enemy_sprites, enemy_start, &player, &maze};

    clyde.update(dt);

    SUBCASE("Clyde's scatter target is the bottom right corner")
    {
        auto correct_target = sf::Vector2f{810,882};
        CHECK(clyde.getScatterTarget() == correct_target);
    }

    clyde.ChaseMode();
    clyde.update(dt);

    SUBCASE("If Clyde is more than 8 tiles away, Clyde's chase target is the player")
    {
        auto correct_target = player.getSprite().getPosition();
        CHECK(clyde.getChaseTarget() == correct_target);
    }

    player_start = sf::Vector2f{558,306};

    player = Player{player_sprites, player_start, &maze};

    SUBCASE("If Clyde is less than 8 tiles away, Clyde's chase target is his scatter target")
    {
        CHECK(clyde.getChaseTarget() == clyde.getScatterTarget());
    }
}

TEST_CASE("Player dies and loses a life if he collides with an enemy in normal mode")
{
    auto maze = initializeMaze();
    auto tileLength = maze.getTileLength();

    auto player_start = maze.getPlayerStart();
    map<string,texturePtr> player_sprites;
    loadPlayerAssets(player_sprites);
    auto player = Player{player_sprites, player_start, &maze};

    auto dt = tileLength/NORMAL_ENEMY_SPEED;

    map<string,texturePtr> enemy_sprites;
    loadEnemyAssets(enemy_sprites);
    auto blinky = Blinky{enemy_sprites, player_start, &player, &maze};

    auto lives = player.livesLeft();

    collisions(player, blinky);

    CHECK(player.livesLeft() == lives-1);
}

TEST_CASE("Player does not die if it is in super mode and it collides with an enemy in normal mode")
{
    auto maze = initializeMaze();
    auto tileLength = maze.getTileLength();

    auto player_start = maze.getPlayerStart();
    map<string,texturePtr> player_sprites;
    loadPlayerAssets(player_sprites);
    auto player = Player{player_sprites, player_start, &maze};

    auto dt = tileLength/NORMAL_ENEMY_SPEED;

    map<string,texturePtr> enemy_sprites;
    loadEnemyAssets(enemy_sprites);
    auto blinky = Blinky{enemy_sprites, player_start, &player, &maze};

    player.enableSuperMode();
    auto lives = player.livesLeft();

    collisions(player, blinky);

    CHECK(player.livesLeft() == lives);
}

TEST_CASE("Player eats enemy if Player is in normal mode and it collides with an enemy in frightened mode")
{
    auto maze = initializeMaze();
    auto tileLength = maze.getTileLength();

    auto player_start = maze.getPlayerStart();
    map<string,texturePtr> player_sprites;
    loadPlayerAssets(player_sprites);
    auto player = Player{player_sprites, player_start, &maze};

    auto dt = tileLength/NORMAL_ENEMY_SPEED;

    map<string,texturePtr> enemy_sprites;
    loadEnemyAssets(enemy_sprites);
    auto blinky = Blinky{enemy_sprites, player_start, &player, &maze};

    blinky.FrightenedMode();
    auto lives = player.livesLeft();

    collisions(player, blinky);

    CHECK(player.livesLeft() == lives);
    CHECK(blinky.isFrightened() == false);
}

TEST_CASE("Player eats the enemy if it is in Super Mode and it collides with an enemy in frightened mode")
{
    auto maze = initializeMaze();
    auto tileLength = maze.getTileLength();

    auto player_start = maze.getPlayerStart();
    map<string,texturePtr> player_sprites;
    loadPlayerAssets(player_sprites);
    auto player = Player{player_sprites, player_start, &maze};

    auto dt = tileLength/NORMAL_ENEMY_SPEED;

    map<string,texturePtr> enemy_sprites;
    loadEnemyAssets(enemy_sprites);
    auto blinky = Blinky{enemy_sprites, player_start, &player, &maze};

    player.enableSuperMode();
    blinky.FrightenedMode();
    auto lives = player.livesLeft();

    collisions(player, blinky);

    CHECK(player.livesLeft() == lives);
    CHECK(blinky.isFrightened() == false);
}


