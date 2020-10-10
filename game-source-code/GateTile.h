#ifndef GATE_TILE_H
#define GATE_TILE_H

/// \file GateTile.h
/// \brief Contains the class definition for the "GateTile" class, which temporarily closes off regions of the maze before being broken by the player or removed by the keys. This tile also inherits the Subject class

#include "Tile.h"
#include "Subject.h"

/// \class GateTile
/// \brief A class derived from the Tile class

class GateTile : public Tile,  public Subject
{
public:
    /// Default contructor.
    GateTile() {};
    
    /// Constructor.
    ///
    /// Takes an additional parameter above the base class constructor that determines the gate's appearance when broken.
    /// @param position the coordinates of the tile in the form sf::Vector2f{x,y}
    /// @param angle the clockwise angle of rotation for the sprite (degrees)
    /// @param normalTexture a shared pointer to the texture for the normal (unbroken) sprite
    /// @param brokenTexture a shared pointer to the texture for the broken sprite
    GateTile(sf::Vector2f position, float angle, texturePtr normalTexture, texturePtr brokenTexture);
    
    /// Performs the action specific to the gate tile.
    ///
    /// The gate tile enters a broken state (if it was not in the state already), setting the sprite to the broken sprite and becoming a valid movement node. The tile's observers are notified that a Observer::Event::GATE_BROKEN has occured.
    void activate() override;
    
    /// Queries the nodality of the gate tile
    ///
    /// \return true if the gate is broken, and false if it is not
    bool isNode() override;

    
    /// Sets the nodality for the GateTile class
    /// @param isNode a boolean that is true if the gates are to be considered as movement nodes, and false if not
    static void isNode(bool isNode) {isNode_ = isNode;}

private:
    static bool isNode_;
    bool isBroken_ = false;
    sf::Sprite brokenSprite_;
};

#endif
