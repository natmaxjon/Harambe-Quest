#ifndef PLAYER_H
#define PLAYER_H

/** \file Player.h
    \brief Contains the class definition for the "Player" class, which provides the object
    controlled by a user during the game.
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Configuration.h"
#include "Character.h"
#include "CharacterState.h"
#include "Maze.h"
#include "Observer.h"
#include "Subject.h"

#include <memory>
#include <stack>

/** \class Player
 *  \brief A class derived mainly from the Character class
 *
 *  The player is inherited from the Character class, which provides
 *  the basic movement and directional functionality. This derived class
 *  acts as state machine, maintaining and updating the various states a
 *  player can be in, and then delegating the required motion and updates
 *  to the current state.
 *
 *  The class also inherits from Observer and Subject, according to the Observer
 *  Pattern of programming, which decreases the coupling to other objects.
 *  As it is implemented, it is an observer of maze objects and observed by the
 *  Scoreboard and the Soundboard.
 */

class Player : public Character, public Observer, public Subject
{
    public:

        /** \brief Default constructor for Player class */
        Player() {}

        /** \brief Constructor for Player class
         *
         *  Initialises a Character object using the Character constructor, as well as
         *  as some of its own data members such as the number of lives.
         *
         *  \param textures, a map<string,texturePtr> which maps a label to a texture pointer
         *  \param position, an sf::Vector2f which contains the x and y coordinates of the
         *  default and initial position of the player
         *  \param maze, a pointer to the Maze
         */
        Player(map<string,texturePtr> textures, sf::Vector2f position, mazePtr maze);

        /** \brief Default destructor for Player class */
        ~Player();

        /** \brief Sets the future direction to UP
         *
         *  This function provides the interface for moving up (if possible), by setting
         *  the future direction vector to UP, which is sf::Vector2f{0,-1}, a constant.
         */
        void Up();

        /** \brief Sets the future direction to DOWN
         *
         *  This function provides the interface for moving down (if possible), by setting
         *  the future direction vector to DOWN, which is sf::Vector2f{0,1}, a constant.
         */
        void Down();

        /** \brief Sets the future direction to RIGHT
         *
         *  This function provides the interface for moving right (if possible), by setting
         *  the future direction vector to RIGHT, which is sf::Vector2f{1,0}, a constant.
         */
        void Right();

        /** \brief Sets the future direction to LEFT
         *
         *  This function provides the interface for moving left (if possible), by setting
         *  the future direction vector to LEFT, which is sf::Vector2f{-1,0}, a constant.
         */
        void Left();

        /** \brief Updates the Player based on a time interval, dt
         *
         *  This function overrides the abstract function provided by the base class, Character.
         *  Whatever changes need to be made to the Player object are made in this function.
         *  First, any state changes are carried out and implemented, such as changing from a
         *  default state to a super state. Secondly, the actual update functionality is delegated
         *  to the current state of the Player, which is represented by a shared pointer to the state,
         *  within an STL stack (See \ref Character). All movements are based on some time increment
         *  dt, which allows movement and mechanics to be smooth and processor independent.
         *
         *  \param dt, the time increment in milliseconds since the function was last called
         */
        void update(float dt) override;

        /** \brief Animates the Player based on a time interval, dt
         *
         *  This function overrides the abstract function provided by the base class, Character.
         *  The player sprite is animated, based on the time interval provided. The animate function
         *  is called with 'textureKey' as a parameter. This is a key to the map of textures. Using
         *  the selected texture along with the time passed in, the function determines which texture
         *  to use, as well as which frame to select. It also enlarges the sprite if the Player is in
         *  Super Mode.
         *
         *  \param dt, the time increment in milliseconds since the function was last called
         */
        void animate(float dt, string textureKey)override;

        /** \brief Performs action based on event passed in by Subjects
         *
         *  Player is an Observer of maze objects such as power pellets and super pellets.
         *  With important changes, subjects will notify Observers, which can then act as
         *  required.
         *
         *  \param event: The event in this case, is an enumeration class defined in Observer.h
         *  It is only important if it is a POWER_PELLET_EATEN, or SUPER_PELLET_EATEN, for which
         *  the player will then change state accordingly. Other events the Player does not care
         *  about do not have any impact.
         */
        void onNotify(Event event) override;

        /** \brief Returns the speed of the player object in Super Mode
         *
         *  The speed depends on three things: the default speeed, defined as a constant, the percentage
         *  increment per level, also defined as a constant, and the level number. This function calculates
         *  the speed in Super Mode (in pixels per millisecond) and returns it as a float.
         *  If the speed is higher than some maximum, the maximum is returned.
         *
         *  \returns The speed of the player as a floating number, in pixels per millisecond
         */
        float SuperSpeed();

        /** \brief Returns the speed of the player object in the Default State
         *
         *  The speed depends on three things: the default speeed, defined as a constant, the percentage
         *  increment per level, also defined as a constant, and the level number. This function calculates
         *  the speed while in the default state (in pixels per millisecond) and returns it as a float.
         *  If the speed is higher than some maximum, the maximum is returned.
         *
         *  \returns The speed of the player as a floating number, in pixels per millisecond
         */
        float NormalSpeed();

        /** \brief Resets the player object after the player dies
         *
         *  When a life is lost, the player is reset by clearing the state stack, setting the default state,
         *  resetting the position to the initial position, and setting the direction vectors to their default
         *  values.
         */
        void reset();

        /** \brief Super Mode is enabled, including adding the PlayerSuperState
         *
         *  If called, this function enables Super Mode by changing the the boolean 'super_mode_'
         *  flag to true, and adding the PlayerSuperState to the Player state stack.
         */
        void enableSuperMode();

        /** \brief Super Mode is disabled, including removing the PlayerSuperState
         *
         *  If called, this function disables Super Mode by changing the the boolean 'super_mode_'
         *  flag to false, and removing the top state, PlayerSuperState, from the Player state stack.
         */
        void disableSuperMode();

        /** \brief Adds a Player Eating State
         *
         *  This function adds a Player Eating state, which is entered upon colliding with an enemy in the
         *  Frightened state. It temporarily pauses movement, and animates accordingly. Player is not interactive
         *  whilst in this state, which lasts for a short period of time specified by a constant in 'Configuration.h'
         */
        void eat();

        /** \brief Adds a Player Dead State
         *
         *  This function adds a Player Dead state, which is entered upon colliding with an enemy NOT in the frightened
         *  state. It temporarily pauses movement, and animates accordingly. Player is not interactive whilst in this
         *  state, which lasts for a short period of time specified by a constant in 'Configuration.h'
         */
        void die();

        /** \brief Checks if the Player object is in Super Mode
         *
         *  \returns True if the player is in Super Mode
         *  \returns False if the player is not in Super Mode
         */
        bool isSuper();

        /** \brief Returns the number of lives left
         *
         *  \returns An integer ranging from 0 to the maximum number of lives determined by
         *  the constant in 'Configuration.h'
         */
        int livesLeft();

    protected:

    private:

        bool super_mode = false;
        bool eatMode_ = false;
        int ghostsEaten_ = 0;
        float timeEating_ = 0;
        int numLives;

};

#endif
