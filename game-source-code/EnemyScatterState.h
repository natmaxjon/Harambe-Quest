#ifndef ENEMY_SCATTER_STATE_H
#define ENEMY_SCATTER_STATE_H

/** \file EnemyScatterState.h
    \brief Contains the class definition for the "EnemyScatterState" class.
*/

#include "Enemy.h"
#include "EnemyMovingState.h"


/** \class EnemyScatterState
 *  \brief Class representing Enemy's Scatter State
 *
 *  This class is derived from the EnemyMovingState class,
 *  and determines the behaviour of an enemy while in the
 *  Scatter state.
 */
class EnemyScatterState : public EnemyMovingState
{
    public:
        /** \brief Constructor for EnemyScatterState class with initialisation list

            Constructs an EnemyMovingState object

            \param enemy, a pointer to the enemy
            \param maze, a pointer to the maze
        */
        EnemyScatterState(enemyPtr  enemy, mazePtr maze);

        /** \brief Destructor for EnemyScatterState */
        virtual ~EnemyScatterState() {}

        /** \brief Updates the enemy by moving towards the Scatter Target and animates the enemy accordingly
         *
         *  This function increments its own time in the state by the value dt.
         *  If the time for the Scatter state, defined in the Configuration header file, has
         *  passed, the state is removed, and the enemy is set to be in Chase Mode
         *  again, using the enemy's ChaseMode() function.
         *
         *  The next move is found by finding an available neighbouring node which
         *  minimises the distance between the current tile and the scatter target.
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

    private:
        float timeInState_ = 0;

};

#endif
