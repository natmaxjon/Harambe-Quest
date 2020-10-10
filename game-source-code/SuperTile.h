#ifndef SUPER_TILE_H
#define SUPER_TILE_H

/// \file SuperTile.h
/// \brief Contains the class definition for the "SuperTile" class, which is one of the tile types that can be eaten by the player in order to complete a maze level and increase the score

#include "Tile.h"
#include "Subject.h"

/// \class SuperTile
/// \brief A class derived from the Tile class. This tile also inherits the Subject class

class SuperTile : public Tile, public Subject
{
public:
    /// Default constructor
    using Tile::Tile;
    
    /// Performs the action specific to the super tile.
    ///
    /// The Maze class's food count is decremented and the super tile is set for removal. The tile's observers are notified that a Observer::Event::SUPER_PELLET_EATEN has occured.
    void activate() override;
    
    /// Queries the nodality of the super tile
    ///
    /// \return true
    bool isNode() override {return true;}
};

#endif
