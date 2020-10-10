#ifndef TILE_H
#define TILE_H

/// \file Tile.h
/// \brief Contains the class definition for the "Tile" class, which will be inherited by each tile type.

#include <SFML/Graphics.hpp>
#include "Configuration.h"
#include <memory>

using namespace std;

/// \class Tile
/// \brief Base class for all the tile types in the maze.
///
/// This class is the base class which will be inherited by each tile
/// type within the maze, providing the common interface for tiles
/// to be activated, updated and queried. Functionality common to all
/// tiles such as setting the tile for removal and querying the sprite
/// properties are also defined here.

class Tile
{
public:
    typedef shared_ptr<sf::Texture> texturePtr; /**< Alias for a pointer to a sf::Texture, to improve readability */
    
    /// Default constructor.
    Tile() {};
    
    /// Constructor.
    ///
    /// @param position the coordinates of the tile in the form sf::Vector2f{x,y}
    /// @param angle the clockwise angle of rotation for the sprite (degrees)
    /// @param texture a shared pointer to the texture for the sprite
    Tile(sf::Vector2f position, float angle, texturePtr texture);
    
    /// Destructor.
    virtual ~Tile() {}

    /// Performs the action specific to the tile.
    ///
    /// This function can be overloaded by the derived tile types to execute a
    /// specific action
    virtual void activate() {};
    
    /// Updates the tile state and/or its appearance.
    ///
    /// (to be used for animation purposes at a later date)
    virtual void update() {};

    /// Queries the nodality of the tile
    ///
    /// \return a boolean that is true if the tile should be considered as a valid
    /// movement tile, and is false otherwise
    virtual bool isNode() = 0;

    /// Set the tile for removal.
    void remove(){removed_ = true;}
    
    /// Query whether the tile has been set for removal.
    ///
    /// \return a boolean that is true if the tile has been set for removal,
    /// and is false otherwise
    bool isRemoved() {return removed_;}
    
    /// Get current xy position of the tile.
    ///
    /// \return the coordinates of the tile in the form sf::Vector2f{x.y}
    sf::Vector2f getPosition() const {return position_;}
    
    /// Get the angle of the tile sprite
    ///
    /// \return a float representing the angle of the sprite in degrees
    float getAngle() const {return angle_;}
    
    /// Get the current sprite of the tile
    ///
    /// \return the sprite of the tile as an sf::Sprite object
    sf::Sprite getSprite() const {return sprite_;}
    
    /// Set the current sprite for the tile
    /// @param sprite a sprite as an sf::Sprite object
    void setSprite(sf::Sprite sprite) {sprite_ = sprite;}
    
private:
    sf::Vector2f position_{0.f,0.f};
    float angle_;
    sf::Sprite sprite_;
    bool removed_ = false;
};

#endif
