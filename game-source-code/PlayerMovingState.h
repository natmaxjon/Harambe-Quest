#ifndef PLAYER_MOVING_STATE_H
#define PLAYER_MOVING_STATE_H

/** \file PlayerMovingState.h
    \brief Contains the class definition for the "PlayerMovingState" class.
*/

#include "CharacterState.h"
#include "Player.h"
#include "Maze.h"

/** \class PlayerMovingState
 *  \brief Base class for moving player states in Harambe's Quest
 *
 *  This class is derived from the CharacterState class, and acts as
 *  a base class which will be inherited by different Player states.
 *  It is an abstract class which has no implementation of its public
 *  members, and the interface is inherited by its derived classes.
 *  However, this class provides a common 'movePlayer' function which
 *  will be common to all derived classes, since movement mechanics of the
 *  player is always the same but differs in speed.
 */
class PlayerMovingState: public CharacterState
{
    public:
        typedef Player* playerPtr; /**< \typedef for a pointer to a Player, to improve readability */
        typedef Maze* mazePtr;  /**< \typedef for a pointer to a Maze, to improve readability */

        /** \brief Default constructor for PlayerMovingState class */
        PlayerMovingState() {}
        /** \brief Default constructor for PlayerMovingState class */
        virtual ~PlayerMovingState() {}

        /** Abstract function for state specific behaviour*/
        virtual void update(float dt) = 0;
        /** Abstract function for state specific behaviour*/
        virtual void enter() = 0;

    protected:

        /** \brief Moves Player to a valid position, and updates the direction if necessary
         *
         *  This function is a key function in the movement of the player. By using the speed
         *  of the player and the time increment passed in, it determines the distance to move,
         *  in pixels. It then checks the closest node, i.e. available tile, in the direction
         *  it is moving. If, at the node, the future direction of the player is a valid move,
         *  _and_ the distance to the node is _less_ than the distance it needs to move, it
         *  moves in the same direction to the node, moves in the future direction to the
         *  distance between the total distance and the node distance, and updates the direction.
         *  If no move is available, or if the distance to the node is _greater_ than the
         *  distance it will move, it continues in the same direction. However, if the future
         *  direction is the reverse of the current direction, i.e., the player wants to turn
         *  around, this can happen freely.
         *
         *  If at the edge of the maze and there is a tunnel to the other side, the player's
         *  movement can wrap around.
         */
        void movePlayer(float dt, float speed, playerPtr  player_, mazePtr maze_);

    private:
};

#endif
