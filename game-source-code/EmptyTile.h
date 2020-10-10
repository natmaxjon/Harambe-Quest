#ifndef EMPTY_TILE_H
#define EMPTY_TILE_H

/// \file EmptyTile.h
/// \brief Contains the class definition for the "EmptyTile" class, which serves as a placeholder tile in the maze array.

#include "Tile.h"

/// \class EmptyTile
/// \brief A class derived from the Tile class
///
/// This class accepts the default behaviour of the base class Tile, except that it identifies itself as a valid movement node.

class EmptyTile : public Tile
{
public:
    
    /// Contructor is the same as the Tile class
    using Tile::Tile;
    
    /// Queries the nodality of the empty tile
    ///
    /// \return true
    bool isNode() override {return true;}
};

#endif
