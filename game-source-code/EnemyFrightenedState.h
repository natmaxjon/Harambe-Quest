#ifndef ENEMY_FRIGHTENED_STATE_H
#define ENEMY_FRIGHTENED_STATE_H

/** \file EnemyFrightenedState.h
    \brief Contains the class definition for the "EnemyFrightenedState" class.
*/

#include "Enemy.h"
#include "EnemyMovingState.h"
#include <ctime>

/** \class EnemyFrightenedState
 *  \brief Class representing Enemy's Frightened State
 *
 *  This class is derived from the EnemyMovingState class,
 *  and determines the behaviour of an enemy while in the
 *  frightened state.
 */

class EnemyFrightenedState : public EnemyMovingState
{
    public:
        /** \brief Constructor for EnemyFrightenedState class with initialisation list

            Constructs an EnemyMovingState object

            \param enemy, a pointer to the enemy
            \param maze, a pointer to the maze
        */
        EnemyFrightenedState(enemyPtr  enemy, mazePtr maze);

        /** \brief Destructor for EnemyFrightenedState */
        virtual ~EnemyFrightenedState() {}

        /** \brief Updates the enemy by moving randomly and animates the enemy accordingly
         *
         *  This function increments its own time in the state by the value dt.
         *  If the time for the Frightened state, defined in the Configuration header file, has
         *  passed, the state is removed, and the enemy reverts to the previous state.
         *
         *  By using the findRandomMove() function, the valid moves are searched and a random
         *  move is selected. The enemy is then updated to move in the direction of the
         *  random move, at its specified frightened state speed.
         *
         *  The function also determines which textureKey to use based on its current
         *  direction, and calls the 'animate' function of the enemy.
         *
         *  \param dt, the time interval in milliseconds since the last function call
         */
        void update(float dt) override;

        /** \brief Enables interactivity of the Enemy upon entering the state
         *
         *  By checking if the Enemy is interactive, and calling the toggleInteractivity()
         *  function if not, the Enemy is set to be interactive.
         */
        void enter() override;

    protected:

    private:
        float timeInState_ = 0;

        sf::Vector2f findRandomMove();
};

#endif // Enemy_POWER_STATE_H
