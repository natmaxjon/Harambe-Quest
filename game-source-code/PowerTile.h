#ifndef POWER_TILE_H
#define POWER_TILE_H

/// \file PowerTile.h
/// \brief Contains the class definition for the "PowerTile" class, which is one of the tile types that can be eaten by the player in order to complete a maze level and increase the score

#include "Tile.h"
#include "Subject.h"

/// \class PowerTile
/// \brief A class derived from the Tile class. This tile also inherits the Subject class

class PowerTile : public Tile, public Subject
{
public:
    /// Default constructor
    using Tile::Tile;
    
    /// Performs the action specific to the power tile.
    ///
    /// The Maze class's food count is decremented and the power tile is set for removal. The tile's observers are notified that a Observer::Event::POWER_PELLET_EATEN has occured.
    void activate() override;
    
    /// Queries the nodality of the power tile
    ///
    /// \return true
    bool isNode() override {return true;}
};

#endif
