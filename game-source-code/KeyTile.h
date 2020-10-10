#ifndef KEY_TILE_H
#define KEY_TILE_H

/// \file KeyTile.h
/// \brief Contains the class definition for the "KeyTile" class, which is used to open the gates that correspond to it

#include "Tile.h"
#include "Subject.h"

/// \class KeyTile
/// \brief A class derived from the Tile class. This tile also inherits the Subject class

class KeyTile : public Tile, public Subject
{
public:
    typedef shared_ptr<Tile> tilePtr; /**\typedef for a pointer to a Tile, to improve readability */

    /// Default constructor
    KeyTile() {};
    
    /// Constructor
    /// @param position the coordinates of the tile in the form sf::Vector2f{x,y}
    /// @param angle the clockwise angle of rotation for the sprite (degrees)
    /// @param texture a shared pointer to the texture for the sprite
    /// @param gates a vector of shared pointers referring to the gates this key should open
    KeyTile(sf::Vector2f position, float angle, texturePtr texture, vector<tilePtr> gates);
    
    /// Performs the action specific to the key tile.
    ///
    /// All the gates associated with this key tile are set for removal, along with the key itself. The tile's observers are notified that a Observer::Event::KEY_EATEN has occured.
    void activate() override;
    
    /// Queries the nodality of the key tile
    ///
    /// \return true
    bool isNode() override {return true;}

private:
    vector<tilePtr> gates_;

};

#endif
