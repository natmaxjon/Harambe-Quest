#ifndef PLAYER_SUPER_STATE_H
#define PLAYER_SUPER_STATE_H

/** \file PlayerSuperState.h
    \brief Contains the class definition for the "PlayerSuperState" class.
*/

#include "PlayerMovingState.h"
#include "Player.h"

/** \class PlayerSuperState
 *
 *  This class is  represents the Player's Super State. It inherits from PlayerMovingState
 *  which inherits from CharacterState. While in Super Mode, this state is active and determines
 *  the movement as well as animation of the player. When time runs out, the state is removed.
 */

class PlayerSuperState : public PlayerMovingState
{
    public:
        typedef Player* playerPtr; /**< \typedef for a pointer to a Player, to improve readability */
        typedef Maze* mazePtr;  /**< \typedef for a pointer to a Maze, to improve readability */

        /** \brief Constructor for PlayerSuperState
         *
         *  Constructs the PlayerSuperState and initialises the pointer to the maze
         *  as well as to the player.
         *
         * \param player, a pointer to the Player
         * \param maze, a pointer to the Maze
         *
         */

        PlayerSuperState(playerPtr  player, mazePtr maze): player_{player}, maze_{maze}{}

        /** \brief Destructor for PlayerSuperState */
        virtual ~PlayerSuperState() {}

        /** \brief Updates the position and animation based on time interval dt
         *
         *  This function increments its own time in the state by the value dt.
         *  If the time for this state, defined in the Configuration header file, has
         *  passed, the state is removed.
         *
         *  The function then calls on the 'movePlayer' function, passing the player's
         *  speed in super mode as a parameter. It also sets gate tiles in the maze to
         *  be of a node type, and activates whichever tile it is on, which has different
         *  behaviour depending on the tile.
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
        float timeInState_ = 0;

        string getTextureName();
};

#endif // PLAYER_SUPER_STATE_H
