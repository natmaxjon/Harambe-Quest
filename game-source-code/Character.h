#ifndef CHARACTER_H
#define CHARACTER_H

/** \file Character.h
    \brief Contains the class definition for a "character" class, which will be inherited by the player as
    well as enemies
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <stack>
#include <cmath>

#include "CharacterState.h"
#include "Maze.h"

/** \class Character
 *  \brief Base class for characters
 *
 *  This class is a base class which will be inherited by multiple
 *  characters. It is one of the main classes which provides core
 *  functionality common to all characters, such as controlling the
 *  overall movement, as well as directionality, and providing functions
 *  which characters can provide their own implementations for
 *
 *  There are some functions and data members with common
 *  functionality, so these have been defined here. Functions which
 *  require distinct functionality have been declared as being abstract,
 *  which will prevent a base "Character" object from being declared.
 *
 */

class Character
{
    public:
        typedef std::shared_ptr<CharacterState> charStatePtr; /**< Alias for a shared pointer to CharacterState */
        typedef shared_ptr<sf::Texture> texturePtr; /**< Alias for a shared pointer to sf::Texture */
        typedef Maze* mazePtr; /**< Alias for a pointer to a Maze, to improve readability */

        /** \brief Default constructor for Character class */
        Character(){};

        /** \brief Constructor for Character class
         *
         *  The constructor initialises a few of the members of each character,
         *  such as the map of textures, the initial and default positions, as
         *  well as a pointer to the Maze.
         */
        Character(map<string,texturePtr> textures, sf::Vector2f position, mazePtr maze);

        /** \brief Destructor for Character class */
        virtual ~Character() {};

        /** \brief Function which returns the Character sprite
         *
         *  \return sf::Sprite for the character
         */
        sf::Sprite getSprite();

        /** \brief Returns the current direction of the character
         *
         *  Directions are defined as being an sf::Vector2f since SFML makes extensive
         *  use of this type. The x-component refers to either left, if -1, or right,
         *  if 1, and the y-component refers to up or down (if -1 or 1) respectively;
         *
         *  \return sf::Vector2f in the form {x,y}
         */
        sf::Vector2f currentDir() const;

        /** \brief Returns the future or intended direction of the character
         *
         *  Directions are defined as being an sf::Vector2f since SFML makes extensive
         *  use of this type. The x-component refers to either left, if -1, or right,
         *  if 1, and the y-component refers to up or down (if -1 or 1) respectively;
         *
         *  \return sf::Vector2f in the form {x,y}
         */
        sf::Vector2f futureDir() const;

        /** \brief Sets the current direction to the future direction */
        void updateDir();

        /** \brief Retrieves the current tile that the Character object's position is in
         *
         *  This function uses the Maze functionality already present to retrieve the position
         *  of the current tile the character is on.
         *
         *  \returns An sf::Vector2f containing the x and y components of the position of the
         *  current tile.
         */
        sf::Vector2f getCurrentTile();

        /** \brief Adds a character state
         *
         *  Allows for a new state to be added when the states of the character
         *  are updated. It provides a default implementation which can be overridden
         *  by derived classes.
         *
         *  \param state: This a shared pointer to the new state to be added
         */
        virtual void addCharState(charStatePtr state);

        /** \brief Removes a character state
         *
         *  Allows for the current state to be removed when the states of the character
         *  are updated. It provides a default implementation which can be overridden
         *  by derived classes.
         *
         *  \param state: This a shared pointer to the new state to be added
         */
        virtual void removeCharState();

        /** \brief  Updates the state of the character
         *
         *  The states are held within an STL stack so if a state is marked to be added,
         *  it will be pushed onto the top of the stack. If the current state needs to
         *  be removed, it will also pop the state off
         */
        virtual void updateCharState();

        /** \brief  Updates the character
         *
         *  This is an abstract function which requires the derived class to provide an
         *  implementation, as necessary, since update functionality is different depending on
         *  the derived class.
         *
         *  \param dt: This is a float of the time which has elapsed since the last call
         */
        virtual void update(float dt) = 0;

        /** \brief  Animates the character
         *
         *  This is an abstract function which requires the derived class to provide an
         *  implementation, as necessary, since animation is different depending on
         *  the derived class.
         *
         *  \param dt: This is a float of the time which has elapsed since the last call
         *  \param textureKey: A string which maps to a texture stored in the texture map
         *         of the character
         */
        virtual void animate(float dt, string textureKey) = 0;

        /** \brief Moves the character by a specified amount
         *
         *  The character's position (an sf::Vector2f) and sprite (sf::Sprite) position
         *  is changed by some amount, specified by the parameter. It is simply added
         *  to the current position using the binary += operator.
         *
         *  \param delta: An sf::Vector2f which contains the required change in x and y
         *  coordinates.
         */
        void moveCharacter(const sf::Vector2f& delta);

        /** \brief Checks if the character is in an interactive or non-interactive state
         */
        bool isInteractive() const;
        /** \brief Toggles the interactivity of the character
         *
         *  If a character is interactive, this will disable the interactivity, and the
         *  opposite will happen if it is non-interactive.
         */
        void toggleInteractivity();

        /** \brief Sets the level number across all Characters
         *
         *  The level number should always be the same for all characters so it is set
         *  via static functions and members.
         *
         *  \param lvlNumber: The current level number
         */
        static void setLevelNumber(const int& lvlNumber);

    protected:



        texturePtr texture_;
        sf::Sprite sprite_;
        sf::Vector2f position_;
        sf::Vector2f default_position_;

        static int lvlNumber_;

        map<string,texturePtr> stateTextures;
        float animateTime = 0;

        std::stack<charStatePtr> char_states_;
        bool is_removing = false;
        bool is_adding = false;
        charStatePtr new_state_;
        mazePtr maze_;

        sf::Vector2f current_dir_;
        sf::Vector2f future_dir_;
        float speed_;

        bool interactive_ = true;
    private:
};

#endif // CHARACTER_H
