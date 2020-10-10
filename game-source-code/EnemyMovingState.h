#ifndef ENEMY_MOVING_STATE_H
#define ENEMY_MOVING_STATE_H

/** \file EnemyMovingState.h
    \brief Contains the class definition for the "EnemyMovingState" class.
*/

#include "CharacterState.h"
#include "Enemy.h"
#include "Maze.h"

#include <vector>

/** \class EnemyMovingState
 *  \brief Base class for moving enemy states
 *
 *  This class is derived from the CharacterState class, and acts as
 *  a base class which will be inherited by different Enemy states.
 *  It is an abstract class which has no implementation of its public
 *  members, and the interface is inherited by its derived classes.
 *  However, this class provides a common 'moveEnemy' function which
 *  will be common to all derived classes, since movement mechanics of the
 *  enemy is always the same but differs in destination.
 */
class EnemyMovingState: public CharacterState
{
    public:
        typedef Enemy* enemyPtr; /**< \typedef for a pointer to an Enemy, to improve readability */
        typedef Maze* mazePtr;  /**< \typedef for a pointer to a Maze, to improve readability */
        /** \brief Default constructor for EnemyMovingState class */
        EnemyMovingState() {}

        /** \brief Constructor for EnemyMovingState class with initialisation list

            \param enemy, a pointer to the enemy
            \param maze, a pointer to the maze
        */
        EnemyMovingState(enemyPtr enemy, mazePtr maze): enemy_{enemy}, maze_{maze} {}

        /** \brief Default destructor for EnemyMovingState class */
        virtual ~EnemyMovingState() {}

        /** \brief Abstract 'update' function implemented by derived classes, to execute state specific behaviour */
        virtual void update(float dt) = 0;

        /** \brief Abstract 'enter' function implemented by derived classes, to execute state specific behaviour */
        virtual void enter() = 0;

    protected:

        void moveEnemy(float dt, float speed);
        sf::Vector2f findNextMove(sf::Vector2f target);
        std::vector<sf::Vector2f> lookAround();

        enemyPtr enemy_;
        mazePtr maze_;

    private:



};

#endif
