#ifndef PLAYER_EAT_STATE_H
#define PLAYER_EAT_STATE_H
/** \file PlayerEatState.h
    \brief Contains the class definition for the "PlayerEatState" class.
*/

#include "CharacterStopState.h"
#include "Player.h"
#include "Maze.h"


/** \class PlayerEatState
 *  \brief Class representing the Player State while eating an enemy
 *
 *  This class is derived from the CharacterStopState class, and represents
 *  the state of the player when eating an enemy. Like other Character States,
 *  this state class has functionality to update the Player itself. However,
 *  only animations are updated since the Player does not move in this state.
 */
class PlayerEatState: public CharacterStopState
{
    public:

        /** \brief Constructor for PlayerEatState
         *
         *  Constructs the PlayerEatState object and initialises the pointer to the maze
         *  as well as to the player.
         *
         * \param player, a pointer to the Player
         * \param maze, a pointer to the Maze
         *
         */
        PlayerEatState(playerPtr player, mazePtr maze);

        /** \brief Destructor for PlayerEatState */
        virtual ~PlayerEatState() {}

        /** \brief Updates the Player Animation based on a time interval dt
         *
         *  This function increments its own time in the state by the value dt.
         *  If the time for this state, defined in the Configuration header file, has
         *  passed, the state is removed, and the player is set to be interactive again.
         *
         *  The function determines which textureKey to use based on its current
         *  direction, and calls the 'animate' function of the player.
         *
         *  \param dt, the time interval in milliseconds since the last function call
         */
        void update(float dt) override;

        /** \brief Disables interactivity of the Player upon entering the state
         *
         *  By checking if the player is interactive, and calling the toggleInteractivity()
         *  function if so, the player is set to be non-interactive.
         */
        void enter() override;

    protected:


    private:
        playerPtr  player_;
        mazePtr maze_;
        float timeInState_ = 0;

};

#endif
