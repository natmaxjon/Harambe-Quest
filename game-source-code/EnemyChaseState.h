#ifndef ENEMY_CHASE_STATE_H
#define ENEMY_CHASE_STATE_H

/** \file EnemyChaseState.h
    \brief Contains the class definition for the "EnemyChaseState" class.
*/

#include "Enemy.h"
#include "EnemyMovingState.h"
#include "EnemyScatterState.h"


/** \class EnemyChaseState
 *  \brief Class representing Enemy's Chase State
 *
 *  This class is derived from the EnemyMovingState class,
 *  and determines the behaviour of an enemy while in the
 *  chase state.
 */

class EnemyChaseState : public EnemyMovingState
{
    public:
        /** \brief Constructor for EnemyChaseState class with initialisation list

            Constructs an EnemyMovingState object

            \param enemy, a pointer to the enemy
            \param maze, a pointer to the maze
        */
        EnemyChaseState(enemyPtr enemy, mazePtr maze);

        /** \brief Destructor for EnemyChaseState */
        virtual ~EnemyChaseState() {}

        /** \brief Updates the enemy by moving towards the Chase Target and animates the enemy accordingly
         *
         *  This function increments its own time in the state by the value dt.
         *  If the time for the Chase state, defined in the Configuration header file, has
         *  passed, the state is removed, and the enemy is set to be in Scatter Mode
         *  again, using the enemy's ScatterMode() function.
         *
         *  The next move is found by finding an available neighbouring node which
         *  minimises the distance between the current tile and the chase target.
         *
         *  The function also determines which textureKey to use based on its current
         *  direction, and calls the 'animate' function of the enemy.
         *
         *  \param dt, the time interval in milliseconds since the last function call
         */
        void update(float dt) override;

        /** \brief Enables interactivity of the Enemy and reverses the direction
         *
         *  By checking if the Enemy is interactive, and calling the toggleInteractivity()
         *  function if not, the Enemy is set to be interactive. The current direction is
         *  also reversed.
         */
        void enter() override;

    protected:

    private:
        float timeInState_ = 0;


};

#endif
