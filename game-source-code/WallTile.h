#ifndef WALL_TILE_H
#define WALL_TILE_H

/// \file WallTile.h
/// \brief Contains the class definition for the "WallTile" class, which serves to define the structure of the maze and limit the character's movements.

#include "Tile.h"

using namespace std;

/// \class WallTile
/// \brief A class derived from the Tile class
///
/// This class accepts the default behaviour of the base class Tile, except that it does not identify itself as a valid movement node.

class WallTile : public Tile
{
public:
     /// Contructor is the same as the Tile class
    using Tile::Tile;

    /// Queries the nodality of the wall tile
    ///
    /// \return false
    bool isNode() override {return false;}
};

#endif
