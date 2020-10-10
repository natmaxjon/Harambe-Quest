#ifndef ENEMY_FROZEN_STATE_H
#define ENEMY_FROZEN_STATE_H


/** \file EnemyFrozenState.h
    \brief Contains the class definition for the "EnemyFrozenState" class.
*/

#include "CharacterStopState.h"
#include "Enemy.h"
#include "Maze.h"


/** \class EnemyFrozenState
 *  \brief Class representing the Enemy State when the Player Dies
 *
 *  This class is derived from the CharacterStopState class, and represents
 *  the state of the enemy after when the player dies. The behaviour of this
 *  state is just that the enemy remains stationary.
 */
class EnemyFrozenState: public CharacterStopState
{
    public:
        typedef Enemy* enemyPtr; /**< \typedef for a pointer to an Enemy, to improve readability */
        typedef Maze* mazePtr;  /**< \typedef for a pointer to a Maze, to improve readability */
        /** \brief Constructor for EnemyFrozenState
         *
         *  Constructs the EnemyFrozenState object and initialises the pointer to the maze
         *  as well as to the enemy.
         *
         * \param enemy, a pointer to the Enemy
         * \param maze, a pointer to the Maze
         *
         */
        EnemyFrozenState(enemyPtr enemy, mazePtr maze);

        /** \brief Destructor for EnemyFrozenState */
        virtual ~EnemyFrozenState() {}

        /** \brief Remains stationary for a set time before resetting
         *
         *  Enemy remains stationary for a time determined by the Configuration file
         *  and then resets using the reset() function.
         *
         *  \param dt, the time interval in milliseconds since the last function call
         */
        void update(float dt) override;
        void enter() override;

    protected:


    private:
        enemyPtr  enemy_;
        mazePtr maze_;
        float timeInState_ = 0;
};

#endif
