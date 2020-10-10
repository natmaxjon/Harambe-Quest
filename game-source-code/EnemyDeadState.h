#ifndef ENEMY_DEAD_STATE_H
#define ENEMY_DEAD_STATE_H
/** \file EnemyDeadState.h
    \brief Contains the class definition for the "EnemyDeadState" class.
*/
#include "EnemyMovingState.h"
#include "Enemy.h"
#include "Maze.h"

/** \class EnemyDeadState
 *  \brief Class representing the Enemy State on being killed
 *
 *  This class is derived from the EnemyMovingState class, and represents
 *  the state of the enemy upon dying. The behaviour of this state is that
 *  the enemy quickly returns to its default position, usually at the centre
 *  of the maze, and is non-interactive.
 */

class EnemyDeadState: public EnemyMovingState
{
    public:

        /** \brief Constructor for EnemyDeadState
         *
         *  Constructs the EnemyDeadnState object and initialises the pointer to the maze
         *  as well as to the enemy.
         *
         * \param enemy, a pointer to the Enemy
         * \param maze, a pointer to the Maze
         *
         */
        EnemyDeadState(enemyPtr enemy, mazePtr maze);

        /** \brief Destructor for EnemyDeadState */
        virtual ~EnemyDeadState() {}

        /** \brief Returns to default position and animated Enemy based on a time interval dt
         *
         *  In this state, the target tile is set to the Enemy's default position and the
         *  speed is set to 3.5 times the normal speed. The Enemy is also non-interactive.
         *  Upon reaching the target tile, the Enemy will remove the current state and
         *  enter Pen State using penState().
         *
         *  The function determines which textureKey to use based on its current
         *  direction, and calls the 'animate' function of the Enemy.
         *
         *  \param dt, the time interval in milliseconds since the last function call
         */
        void update(float dt) override;

        /** \brief Disables interactivity of the Enemy upon entering the state
         *
         *  By checking if the Enemy is interactive, and calling the toggleInteractivity()
         *  function if so, the Enemy is set to be non-interactive.
         */
        void enter() override;

    private:
        float timeInState_ = 0;
};

#endif
