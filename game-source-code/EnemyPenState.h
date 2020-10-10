#ifndef ENEMY_PEN_STATE_H
#define ENEMY_PEN_STATE_H

/** \file EnemyPenState.h
    \brief Contains the class definition for the "EnemyPenState" class.
*/

#include "CharacterStopState.h"
#include "Enemy.h"
#include "Maze.h"


/** \class EnemyPenState
 *  \brief Class representing the Enemy State after dying
 *
 *  This class is derived from the CharacterStopState class, and represents
 *  the state of the enemy after dying. The behaviour of this state is that
 *  the enemy remains inactive and stationary for a short period of time.
 *  Like other Character States, this state class has functionality to update
 *  the Enemy itself. However, only animations are updated since the Enemy
 *  does not move in this state.
 */
class EnemyPenState: public CharacterStopState
{
    public:
        typedef Enemy* enemyPtr; /**< \typedef for a pointer to an Enemy, to improve readability */
        typedef Maze* mazePtr;  /**< \typedef for a pointer to a Maze, to improve readability */

        /** \brief Constructor for EnemyPenState
         *
         *  Constructs the EnemyPenState object and initialises the pointer to the maze
         *  as well as to the enemy.
         *
         * \param enemy, a pointer to the Enemy
         * \param maze, a pointer to the Maze
         *
         */
        EnemyPenState(enemyPtr enemy, mazePtr maze);

        /** \brief Destructor for EnemyPenState */
        virtual ~EnemyPenState() {}

        /** \brief Updates the Enemy Animation based on a time interval dt
         *
         *  This function increments its own time in the state by the value dt.
         *  If the time for the Pen state, defined in the Configuration header file, has
         *  passed, the state is removed, and the enemy is set to be in Scatter Mode
         *  again, using the enemy's ScatterMode() function.
         *
         *  The function determines which textureKey to use based on its current
         *  direction, and calls the 'animate' function of the enemy.
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
