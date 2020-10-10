#ifndef DEFAULT_CHARACTER_STATE_H
#define DEFAULT_CHARACTER_STATE_H

/** \file DefaultCharacterState.h
    \brief Contains the class definition for the "DefaultCharacterState" class.
*/

#include "PlayerMovingState.h"
#include "Player.h"

/** \class DefaultCharacterState
 *
 *  This class is active when the player is in its normal, default state. It inherits from
 *  PlayerMovingState which inherits from CharacterState. Although the name says 'Character',
 *  this state is only for the player and not the enemy.
 */

class DefaultCharacterState : public PlayerMovingState
{
    public:

        /** \brief Constructor for DefaultCharacterState
         *
         *  Constructs the DefaultCharacterState and initialises the pointer to the maze
         *  as well as to the player.
         *
         * \param player, a pointer to the Player
         * \param maze, a pointer to the Maze
         *
         */
        DefaultCharacterState(playerPtr player, mazePtr maze): player_{player}, maze_{maze} {}

        /** \brief Destructor for DefaultCharacterState */
        virtual ~DefaultCharacterState() {}

        /** \brief Updates the position and animation based on time interval dt
         *
         *  The function calls on the 'movePlayer' function, passing the player's
         *  speed in its normal mode as a parameter. It activates whichever tile it is
         *  on, which has different behaviour depending on the tile.
         *
         *  Finally the function determines which textureKey to use based on its current
         *  direction, and calls the 'animate' function of the player.
         *
         *  \param dt, the time interval in milliseconds since the last function call
         */
        void update(float dt) override;
        void enter() override;

    protected:

    private:
        playerPtr  player_;
        mazePtr maze_;

        string getTextureName();
};

#endif
