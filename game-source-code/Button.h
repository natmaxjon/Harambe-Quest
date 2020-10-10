#ifndef BUTTON_H
#define BUTTON_H

/// \file Button.h
/// \brief Contains the class definition for the "Button" class

#include <SFML/Graphics.hpp>
#include "Configuration.h"
#include <memory>

using namespace std;

/// \class Button
/// \brief An object used to receive user input based on the position of the mouse
///
/// The button class is a wrapper for a text-sprite combination. The button class does not perform any actions when clicked, but rather is able to report whether the mouse is contained within its borders. The class in which an instance of the button is contained gives the button its activated behaviour by querying whether the mouse button is clicked while the mouse is hovering over the button. The button updates its visual appearance based on whether it is selected, being hovered over, or neither of these things. Note that the origin of the button is always the centre of the sprite.

class Button: public sf::Drawable
{
public:
    typedef shared_ptr<sf::Font> fontPtr; /**\typedef for a pointer to a sf::Font, to improve readability */
    typedef shared_ptr<sf::Texture> texturePtr; /**\typedef for a pointer to a sf::Texture, to improve readability */

    /// Default constructor.
    Button() {};
    
    /// Destructor.
    ~Button() {};

    /// Constructor.
    /// @param texture a shared pointer to the texture for the button sprite
    /// @param font a shared pointer to the font of the button text
    Button(texturePtr texture, fontPtr font);
    
    /// Constructor.
    /// @param texture a shared pointer to the texture for the button sprite
    Button(texturePtr texture);

    /// Draw the button sprite and text.
    /// @param target Render target to draw to
    /// @param states Current render states
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /// Update the appearance of button.
    ///
    /// This is done by adjusting the colour settings of the button sprite, outline and text according to whether the button is selected, being hovered over, or none of the above
    /// @param window Reference window
    void update(const sf::RenderWindow& window);
    
    /// Select the button.
    ///
    /// This will result in the button's selected colours being displayed regardless of whether the mouse is contained within the button's borders
    void select();
    
    /// Deselect the button.
    ///
    /// This has the opposite effect of the select button, returning the button to its normal state
    void deselect();
    
    /// Toggle selected state of the button.
    ///
    /// If the button was previously selected, deselect it, and if it was previously deselected, select it.
    void toggleSelection();

    /// Query whether the button boundries contain the mouse coordinates.
    /// @param window Reference window
    /// \return boolean that is true when the mouse is within the boundries of the button, and false if it is not
    bool isHover(const sf::RenderWindow& window) const;
    
    /// Set the text displayed on the button.
    /// @param text string containing the button text
    void setString(const string& text);
    
    /// Set the outline thickness of the sprite's global bounds.
    /// @param thickness float representing the outline thickness (pixels)
    void setOutline(float thickness);
    
    /// Set the postion of the button.
    /// @param x float representing the x coordinate
    /// @param y float representing the y coordinate
    void setPosition(float x, float y);
    
    /// Set the postion of the button.
    /// @param position the coordinates of the button in the form sf::Vector2f{x,y}
    void setPosition(sf::Vector2f position);
    
    /// Set the scaling of the button sprite.
    ///
    /// This function completely overwrites the previous scale. The default scale is (1,1)
    /// @param factorX scaling in the x direction
    /// @param factorY scaling in the y direction
    void setSpriteScale(float factorX, float factorY);
    
    /// Set the scaling of the button text.
    ///
    /// This function completely overwrites the previous scale. The default scale is (1,1)
    /// @param factorX scaling in the x direction
    /// @param factorY scaling in the y direction
    void setTextScale(float factorX, float factorY);
    
    /// Set the orientation of the button.
    ///
    /// This function completely overwrites the previous rotation. The default angle is 0 degrees
    /// @param angle angle of rotation in degrees
    void setRotation(float angle);
    
    /// Set the normal colour of all the button components.
    ///
    /// The normal colour shown when the sprite is niether selected nor being hovered over
    /// @param colour normal colour
    void setColour(sf::Color colour);
    
    /// Set the normal colour of all the button components.
    ///
    /// This determines the colour of the text, outline and sprite when the mouse is hovering over the button
    /// @param colour hover colour
    void setHoverColour(sf::Color colour);
    
    /// Set the selected colour of all the button components.
    /// @param colour selected colour
    void setSelectedColour(sf::Color colour);
    
    /// Set the normal, hover and selected colours for the button sprite.
    /// @param normalColour normal sprite colour
    /// @param hoverColour hover sprite colour
    /// @param selectedColour selected sprite colour
    void setSpriteColour(sf::Color normalColour, sf::Color hoverColour, sf::Color selectedColour);
    
    /// Set the normal, hover and selected colours for the button text.
    /// @param normalColour normal text colour
    /// @param hoverColour hover text colour
    /// @param selectedColour hover text colour
    void setTextColour(sf::Color normalColour, sf::Color hoverColour, sf::Color selectedColour);
    
    /// Set the normal, hover and selected colours for the button outline.
    /// @param normalColour normal outline colour
    /// @param hoverColour hover outline colour
    /// @param selectedColour hover outline colour
    void setOutlineColour(sf::Color normalColour, sf::Color hoverColour, sf::Color selectedColour);
    
    /// Get the coordinates of the button.
    /// \return the coordinates of the button in the form sf::Vector2f{x,y}
    sf::Vector2f getPosition() {return position_;}
    
    /// Get the angle of rotation of the button.
    /// \return angle of rotation in degrees
    float getRotation() {return angle_;}

private:
    texturePtr texture_;
    fontPtr font_;
    sf::Sprite sprite_;
    sf::Text text_;
    sf::RectangleShape outline_;
    
    sf::Vector2f position_{0,0};
    sf::Vector2f spriteScale_{1,1};
    sf::Vector2f textScale_{1,1};
    float angle_ = 0.f;
    float hoverOutlineThickness_ = 0.f;

    sf::Color spriteColour_{sf::Color::White};
    sf::Color textColour_{sf::Color::White};
    sf::Color outlineColour_{sf::Color::White};

    sf::Color spriteHoverColour_{sf::Color::Yellow};
    sf::Color textHoverColour_{sf::Color::Yellow};
    sf::Color outlineHoverColour_{sf::Color::Yellow};
    
    sf::Color spriteSelectedColour_{sf::Color::Green};
    sf::Color textSelectedColour_{sf::Color::Green};
    sf::Color outlineSelectedColour_{sf::Color::Green};

    bool isSelected_ = false;
    bool isAlreadySelected_ = false;
    bool isAlreadyHover_ = true;
};

#endif
