#ifndef FRUIT_TILE_H
#define FRUIT_TILE_H

/// \file FruitTile.h
/// \brief Contains the class definition for the "FruitTile" class, which is one of the tile types that can be eaten by the player in order to complete a maze level and increase the score

#include "Tile.h"
#include "Subject.h"

/// \class FruitTile
/// \brief A class derived from the Tile class. This tile also inherits the Subject class

class FruitTile : public Tile, public Subject
{
public:
    /// Default constructor
    using Tile::Tile;
    
    /// Performs the action specific to the fruit tile.
    ///
    /// The Maze class's food count is decremented and the fruit tile is set for removal. The tile's observers are notified that a Observer::Event::KEY_FRUIT_EATEN has occured.
    void activate() override;
    
    /// Queries the nodality of the fruit tile
    ///
    /// \return true
    bool isNode() override {return true;}
};

#endif
