#include "Maze.h"

#include "EmptyTile.h"
#include "WallTile.h"
#include "GateTile.h"
#include "KeyTile.h"
#include "FruitTile.h"
#include "PowerTile.h"
#include "SuperTile.h"

#include <string>
#include <iostream>

Maze::Maze(Data mazeData, Textures mazeTextures, Observers mazeObservers, sf::Vector2f topLeftPos, float tileLength):
mazeData_{mazeData},
mazeTextures_{mazeTextures},
mazeObservers_{mazeObservers},
topLeftPos_{topLeftPos},
tileLength_{tileLength},
width_{mazeData.layout[0].size() * tileLength},
height_{mazeData.layout.size() * tileLength},
offset_{topLeftPos_ + sf::Vector2f{tileLength_/2, tileLength_/2}}
{
    foodCount_ = 0;
    createMaze();
}

void Maze::update()
{
    for (auto& row : maze_)
        for (auto& col : row)
            updateTile(col);
}

void Maze::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    auto walls = vector<tilePtr>{};

    // Draw everything except walls and corners first
    for (auto col = 0; col < mazeData_.layout[0].size(); col++)
    {
        for (auto row = 0; row < mazeData_.layout.size(); row++)
        {
            if (mazeData_.layout[row].at(col) == 'W' || mazeData_.layout[row].at(col) == 'C')
                walls.push_back(maze_[col][row]);
            else
                target.draw(maze_[col][row]->getSprite());
        }
    }

    // Draw walls and corners
    for (auto wall : walls)
        target.draw(wall->getSprite());
}

Maze::tilePtr Maze::getTile(sf::Vector2f position)
{
    auto yPos = static_cast<int>((position.y - topLeftPos_.y)/tileLength_);
    auto xPos = static_cast<int>((position.x - topLeftPos_.x)/tileLength_);

    return maze_[xPos][yPos];
}

vector<sf::Vector2f> Maze::getNodes() const
{
    vector<sf::Vector2f> nodes;

    for (auto row : maze_)
        for (auto col : row)
            if (col->isNode())
                nodes.push_back(col->getPosition());

    return nodes;
}

sf::Vector2f Maze::getPlayerStart() const
{
    auto position = mazeData_.startPos[0];

    return maze_[position.x][position.y]->getPosition();
}


vector<sf::Vector2f> Maze::getEnemyStarts() const
{
    vector<sf::Vector2f> coords;

    auto first = mazeData_.startPos.begin() + 1;
    auto last = mazeData_.startPos.end();
    auto positions = vector<sf::Vector2f>{first, last};

    for (auto pos : positions)
        coords.push_back(maze_[pos.x][pos.y]->getPosition());

    return coords;
}

tuple<sf::Vector2f,sf::Vector2f> Maze::getMazeBounds() const
{
    auto topLeftCorner = topLeftPos_;
    auto bottomRightCorner = topLeftPos_ + sf::Vector2f{width_,height_};

    return make_tuple(topLeftCorner, bottomRightCorner);
}

bool Maze::isClear()
{
    return (foodCount_ <= 0);
}

/*------------- Private helper functions -------------*/

void Maze::updateTile(Maze::tilePtr& tile)
{
    // tile->update(); // Uncomment for tile animations

    if (tile->isRemoved())
    {
        tile = make_shared<EmptyTile>(tile->getPosition(), tile->getAngle(), mazeTextures_.empty);
    }
}

void Maze::createMaze()
{
    vector<Maze::tilePtr> columnOfTiles{};

    for (auto col = 0; col < mazeData_.layout[0].size(); col++)
    {
        columnOfTiles = {};
        for (auto row = 0; row < mazeData_.layout.size(); row++)
        {
            columnOfTiles.push_back(assignTile(row, col));
        }
        maze_.push_back(columnOfTiles);
    }

    applyKeyMap(mazeData_.keyMap);

    for (auto pos : keyPos_)
    {
        auto position = offset_ + sf::Vector2f{get<0>(pos) * tileLength_, get<1>(pos) * tileLength_};
        auto angle = char2Angle(mazeData_.rotationMap[get<1>(pos)].at(get<0>(pos)));

        auto keyTile =  make_shared<KeyTile>(position, angle, mazeTextures_.key, keyMap_[pos]);

        keyTile->addObserver(mazeObservers_.soundBoard);
        maze_[get<0>(pos)][get<1>(pos)] = keyTile;
    }
}

Maze::tilePtr Maze::assignTile(int row, int col)
{
    auto position = offset_ + sf::Vector2f{col * tileLength_, row * tileLength_};
    auto angle = char2Angle(mazeData_.rotationMap[row].at(col));

    switch (mazeData_.layout[row].at(col))
    {
        case 'E':
            return make_shared<EmptyTile>(position, angle, mazeTextures_.empty);
        case 'W':
            return make_shared<WallTile>(position, angle, mazeTextures_.wall);
        case 'C':
            return make_shared<WallTile>(position, angle, mazeTextures_.corner);
        case 'G':
        {
            auto gate = make_shared<GateTile>(position, angle, mazeTextures_.gate, mazeTextures_.brokenGate);
            gate->addObserver(mazeObservers_.soundBoard);
            return gate;
        }
        case 'K':
            keyPos_.push_back(make_tuple(col, row));
            return nullptr;
        case 'F':
        {
            auto fruit = make_shared<FruitTile>(position, angle, mazeTextures_.fruit);
            fruit->addObserver(mazeObservers_.scoreBoard);
            fruit->addObserver(mazeObservers_.soundBoard);
            incrementFoodCount();
            return fruit;
        }
        case 'P':
        {
            auto pellet = make_shared<PowerTile>(position, angle, mazeTextures_.powerPellet);

            pellet->addObserver(mazeObservers_.player);

            for (auto enemy : mazeObservers_.enemies)
                pellet->addObserver(enemy);

            pellet->addObserver(mazeObservers_.scoreBoard);
            pellet->addObserver(mazeObservers_.soundBoard);
            incrementFoodCount();
            return pellet;
        }
        case 'S':
        {
            auto pellet = make_shared<SuperTile>(position, angle, mazeTextures_.superPellet);

            pellet->addObserver(mazeObservers_.player);

            for (auto enemy : mazeObservers_.enemies)
                pellet->addObserver(enemy);
            
            pellet->addObserver(mazeObservers_.scoreBoard);
            pellet->addObserver(mazeObservers_.soundBoard);
            incrementFoodCount();
            return pellet;
        }
        default:
            cout << "Error: No match for layout key" << endl; // Throw Exception
            return make_shared<EmptyTile>(position, angle, mazeTextures_.empty);
    }
}

float Maze::char2Angle(char c) const
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
            cout << "Error: No match for rotation key" << endl;   // Replace with exception
            return 0.f;
    }
}

void Maze::applyKeyMap(posKeyMap keyMap)
{
    vector<tilePtr> gates;

    for (auto& [keyPos, gatePos] : keyMap)
    {
        for (auto& pos : gatePos)
        {
            gates.push_back(maze_[get<0>(pos)][get<1>(pos)]);
        }

        keyMap_[keyPos] = gates;
        gates = {};
    }
}

/*------------- Static data members -------------*/

int Maze::foodCount_ = 0;
