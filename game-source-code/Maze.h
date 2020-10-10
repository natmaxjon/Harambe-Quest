#ifndef MAZE_H
#define MAZE_H

/// \file Maze.h
/// \brief Contains the class definition for the "Maze" class

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Observer.h"

#include <memory>
#include <map>

/// \class Maze
/// \brief An object that stores and manages the 2D array of tiles forming the maze itself
///
/// This class stores the maze as a two-dimensional array of tile pointers, and is responsible for removing a tile when it is set for removal and providing information regarding the maze bounds, character start positions, and the tile at a given coordinate.

using namespace std;

class Maze : public sf::Drawable
{
public:

    typedef shared_ptr<Tile> tilePtr; /**\typedef for a pointer to a Tile, to improve readability */
    typedef map<tuple<int,int>, vector<tuple<int,int>>> posKeyMap; /**\typedef for a map relating a tuple of two ints to a vector of tuples of two ints, to improve readability */
    typedef shared_ptr<sf::Texture> texturePtr; /**\typedef for a pointer to a sf::Texture, to improve readability */
    
    /// \struct A structure containing the data that characterises a maze, specifically the layout, rotation map, key map and start positions
    struct Data
    {
        vector<string> layout;
        vector<string> rotationMap;
        posKeyMap keyMap;
        vector<sf::Vector2f> startPos;
    };

    /// \struct A structure containing the desired texture for each tile in the maze
    struct Textures
    {
        texturePtr empty;
        texturePtr wall;
        texturePtr corner;
        texturePtr gate;
        texturePtr brokenGate;
        texturePtr key;
        texturePtr fruit;
        texturePtr powerPellet;
        texturePtr superPellet;
    };

    /// \struct A structure containing the observers that need to monitor each tile
    struct Observers
    {
        Observer* player;
        vector<Observer*> enemies;
        Observer* scoreBoard;
        Observer* soundBoard;
    };

    /// Default constructor
    Maze() {}
    
    // Destructor
    ~Maze() {}
    
    /// Constructor
    /// @param mazeData a structure containing the maze layout, rotation map, key map and start positions
    /// @param mazeTextures a structure containing the desired texture for each tile in the maze
    /// @param mazeObservers A structure containing the observers that need to monitor each tile
    /// @param topLeftPos the top left coordinates of the maze in the form sf::Vector2f{x,y}
    /// @param tileLength the length of all the tiles in the maze (pixels)
    Maze(Data mazeData, Textures mazeTextures, Observers mazeObservers, sf::Vector2f topLeftPos, float tileLength);

    /// Updates every tile in the array.
    ///
    /// Removing it if it is set for removal and replacing it with an empty tile
    void update();

    /// Overriding of SFML's draw function to control how the maze is drawn
    ///
    /// The wall tile need to be drawn last to ensure that the maze appears visually correct
    /// @param target Render target to draw to
    /// @param states Current render states
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /// Get the tile corresponding to the coordinates provided.
    ///
    /// The tile corresponding to the coordinates is the tile which contains the given coordinate within its area
    /// @param position coordinates in the form sf::Vector2f{x,y}
    ///\return a shared pointer to the tile corresponding to the coordinates provided
    tilePtr getTile(sf::Vector2f position);

    /// Returns a list of the positions of the valid movement nodes in the array
    ///
    /// The array is iterated over and each tile is queries using the isNode() function to determine whether it should be added o the list
    /// \return A vector of positions that are in the form sf::Vector2f{x,y}
    vector<sf::Vector2f> getNodes() const;
    
    /// Gets the starting position for the player within the maze
    /// \return a position in the form sf::Vector2f{x,y}
    sf::Vector2f getPlayerStart() const;

    /// Gets the starting positions of the enemies within the maze
    /// \return a vector of positions in the form sf::Vector2f{x,y}
    vector<sf::Vector2f> getEnemyStarts() const;
    
    /// Gets the bounds of the maze
    ///
    /// The bounds of the maze can be fully described by the top left and bottom right coordinate
    ///\return a tuple containing the coordinates of the top left and the bottom right corners of the maze in the form sf::Vector2f{x,y}
    tuple<sf::Vector2f,sf::Vector2f> getMazeBounds() const;
    
    /// Query whether there are is no more fruit, power pellets or super pellets remaining in the maze
    /// \return true if the sum of fruit, power pellets or super pellets is equal to or less than zero, and is false otherwise
    bool isClear();

    /// Get the length of the tiles in the maze
    /// \return a float representing the tile length (pixels)
    float getTileLength() const {return tileLength_;}
    
    /// Get the width of the maze
    /// \return a float representing the width of the maze
    float getWidth() const {return width_;}
    
    /// Get the height of the maze
    /// \return a float representing the height of the maze
    float getHeight() const {return height_;}
    vector<vector<tilePtr>> getMaze() const {return maze_;} // REMOVE!!!!

    /// Add 1 to the food count
    static void incrementFoodCount() {foodCount_++;}
    
    /// Remove 1 from the food count
    static void decrementFoodCount() {foodCount_--;}

private:
    // Private data members
    Data mazeData_;
    Textures mazeTextures_;
    Observers mazeObservers_;
    sf::Vector2f topLeftPos_;
    float tileLength_;
    float width_;
    float height_;
    sf::Vector2f offset_;

    vector<vector<tilePtr>> maze_;         // NOTE: maze_[x][y] == maze[col][row]
    vector<tuple<int,int>> keyPos_;
    map<tuple<int,int>, vector<tilePtr>> keyMap_;

    static int foodCount_;

    // Private member functions
    void updateTile(Maze::tilePtr& tile);
    void createMaze();
    tilePtr assignTile(int row, int col);
    float char2Angle(char c) const;
    void applyKeyMap(posKeyMap keyMap);
};
#endif
