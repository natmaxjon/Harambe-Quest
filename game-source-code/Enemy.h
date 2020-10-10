#ifndef ENEMY_H
#define ENEMY_H

/** \file Enemy.h
    \brief Contains the class definition for the "Player" class, which provides objects controlled
    by the program itself
*/

#include "Configuration.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Character.h"
#include "Player.h"
#include "Maze.h"
#include "Observer.h"
#include "Subject.h"

#include <vector>
#include <ctime>
#include <memory>

/** \class Enemy
 *  \brief A class derived mainly from the Character class
 *
 *  The Enemy is inherited from the Character class, which provides
 *  the basic movement and directional functionality. This derived class
 *  acts as state machine, maintaining and updating the various states a
 *  an Enemy can be in, and then delegating the required motion and updates
 *  to the current state. However, it is also a base class for different
 *  types of Enemies, which vary in their behaviour. As such, these differences
 *  are handled by the derived classes, and all common functionality is handled
 *  by this class.
 *
 *  The class also inherits from Observer and Subject, according to the Observer
 *  Pattern of programming, which decreases the coupling to other objects.
 *  As it is implemented, it is an observer of maze objects and observed by the
 *  Player, the Scoreboard and the Soundboard.
 */

class Enemy  : public Character, public Observer, public Subject
{
    public:
        typedef Player* playerPtr; /**< Alias for a pointer to a Player, to improve readability */

        /** \brief Default constructor for Enemy class */
        Enemy(){}

        /** \brief Constructor for Enemy class
         *
         *  Initialises an Enemy object by creating aCharacter object using the Character constructor,
         *  as well as some of its own data members such as the pointer to the Player.
         *
         *  \param textures, a map<string,texturePtr> which maps a label to a texture pointer
         *  \param position, an sf::Vector2f which contains the x and y coordinates of the
         *  default and initial position of the player
         *  \param player, a pointer to the Player
         *  \param maze, a pointer to the Maze
         */
        Enemy(map<string,texturePtr> textures, sf::Vector2f position, playerPtr player, mazePtr maze);

        /** \brief Default destructor for Enemy class */
        virtual ~Enemy();

        /** \brief Sets the future direction vector
         *
         *  The future direction vector is updated to the direction vector specified by dir. If dir is
         *  not a valid direction, i.e. not an sf::Vector2f with {x,y} as {-1,0},{1,0},{0,-1}, or {0,1},
         *  nothing happens.
         *
         *  \param dir, an sf::Vector2f containing the new future direction vector.
         */
        void setFutureDir(sf::Vector2f dir);

        /** \brief Performs action based on event passed in by Subjects
         *
         *  Enemy is an Observer of maze objects such as power pellets.
         *  With important changes, subjects will notify Observers, which can then act as
         *  required. If a power pellet is eaten, this causes the Enemy to go into
         *  frightened mode.
         *
         *  \param event: The event in this case, is an enumeration class defined in Observer.h
         *  It is only important if it is a POWER_PELLET_EATEN, for which the enemy will then
         *  change state accordingly.
         */
        void onNotify(Event event) override;

        /** \brief Reverses the current direction
         *
         *  Applies a 180 degree rotation of the current direction vector, which is equivalent to
         *  multiplying the direction vector by -1.0f
         */
        void reverseDir();

        /** \brief Frightened Mode is enabled, including adding EnemyFrightenedState to the state stack.
         *
         *  If called, this function enables Frightened Mode by changing the the boolean 'frightened_'
         *  flag to true, and adding EnemyFrightenedState to the state stack. In Frightened mode, movements
         *  are random and slower than normal.
         */
        void FrightenedMode();

         /** \brief Frightened Mode is disabled, including removing EnemyFrightenedState from the state stack.
         *
         *  If called, this function enables Frightened Mode by changing the the boolean 'frightened_'
         *  flag to true, and adding EnemyFrightenedState to the state stack. The Enemy will then revert to
         *  whichever state was previously active;
         */
        void DisableFrightenedMode();

        /** \brief Chase Mode is enabled by adding EnemyChaseState to the state stack.
         *
         *  If called, this function enables Chase Mode by adding EnemyChaseState to the state stack.
         *  In this state, the Enemy will chase the player.
         */
        void ChaseMode();

         /** \brief Scatter Mode is enabled by EnemyScatterState to the state stack.
         *
         *  If called, this function enables Chase Mode by adding EnemyChaseState to the state stack,
         *  In this state, the Enemy will target a unique scatter target.
         */
        void ScatterMode();

        /** \brief EnemyFrozenState is added to the stack
         *
         *  This happens when the player dies, and the enemy gets frozen for a period of time.
         */
        void PlayerDead();

        /** \brief Returns the speed of the enemy in Frightened Mode
         *
         *  The speed depends on three things: the default speeed, defined as a constant, the percentage
         *  increment per level, also defined as a constant, and the level number. This function calculates
         *  the speed in Frightened Mode (in pixels per millisecond) and returns it as a float.
         *  If the speed is higher than some maximum, the maximum is returned. These constants are defined in
         *  the Configuration header file.
         *
         *  \returns The speed of the enemy while frightened as a floating number, in pixels per millisecond.
         */
        float FrightenedSpeed();

        /** \brief Returns the speed of the enemy in Chase Mode
         *
         *  The speed depends on three things: the default speeed, defined as a constant, the percentage
         *  increment per level, also defined as a constant, and the level number. This function calculates
         *  the speed in Chase Mode (in pixels per millisecond) and returns it as a float.
         *  If the speed is higher than some maximum, the maximum is returned. These constants are defined in
         *  the Configuration header file.
         *
         *  \returns The speed of the enemy while in chase mode as a floating number, in pixels per millisecond.
         */
        float ChaseSpeed();

        /** \brief Returns the speed of the enemy in Scatter mode
         *
         *  The speed depends on three things: the default speeed, defined as a constant, the percentage
         *  increment per level, also defined as a constant, and the level number. This function calculates
         *  the speed in Scatter Mode (in pixels per millisecond) and returns it as a float.
         *  If the speed is higher than some maximum, the maximum is returned. These constants are defined in
         *  the Configuration header file.
         *
         *  \returns The speed of the enemy while in scatter mode as a floating number, in pixels per millisecond.
         */
        float ScatterSpeed();

        /** \brief Checks if the enemy is in Frightened Mode
         *
         *  \returns The value of the boolean flag, frightened_
         */
        bool isFrightened();

        /** \brief Resets the enemy object after the player dies
         *
         *  When a player's life is lost, the enemy is also reset by clearing the state stack, adding EnemyScatterState
         *  to it, resetting the position to the initial position, and setting the direction vectors to their default
         *  values.
         */
        void reset();

        /** \brief EnemyDeadState is added to the stack
         *
         *  In addition to adding EnemyDeadState to the stack, frightened mode is also disabled and Observers of the
         *  enemy are notified of the event.
         */
        void die();

        /** \brief EnemyPenState is added to the stack
         */
        void penState();

        /** \brief Updates the Enemy based on a time interval, dt
         *
         *  This function is not given an implementation, instead leaving it to the derived classes
         *  to provide an implementation.
         *
         */
        virtual void update(float dt) = 0;

        /** \brief Animates the Enemy based on a time interval, dt
         *
         *  This function overrides the abstract function provided by the base class, Character.
         *  The enemy sprite is animated, based on the time interval provided. The animate function
         *  is called with 'textureKey' as a parameter. This is a key to the map of textures. Using
         *  the selected texture, the current direction and the time passed in, it determines which
         *  texture to use, as well as which frame in the texture to select.
         *
         *  \param dt, the time increment in milliseconds since the function was last called
         *  \param textureKey, a string which contains a key linked to a texture pointer
         */
        virtual void animate(float dt, string textureKey) override;

        /** \brief Returns the chase target
         *
         *  Returns the chase target, which is different depending on the the enemy behaviour. As such,
         *  it is an abstract function with implementation provided by the derived class.
         */
        virtual sf::Vector2f getChaseTarget() = 0;

        /** \brief Returns the scatter target
         *
         *  Returns the scatter target, which is different depending on the the enemy behaviour. As such,
         *  it is an abstract function with implementation provided by the derived class.
         */
        virtual sf::Vector2f getScatterTarget() = 0;

        /** \brief Returns the Default position of the enemy
         *
         *  \returns an sf::Vector2f containing the x and y coordinates of the enemy's default position.
         */
        virtual sf::Vector2f getPenPosition();

    protected:

        playerPtr player_;

        sf::Color default_color_;
        bool frightened_ = false;
        sf::Vector2f default_dir_;

    private:



};

#endif // ENEMY_H
