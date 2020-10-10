#ifndef INKY_H
#define INKY_H

/** \file Inky.h
 *  \brief Contains the class definition of Inky, derived from Enemy
 */

#include "Enemy.h"
#include "Player.h"
#include "Maze.h"
#include "Blinky.h"

/** \class Inky
 *  \brief One of the four derived Enemy classes
 *
 *  Each enemy derived class has distinct behaviour. This class manages its own states,
 *  as well as delegates its update functionality to its current state.
 *
 *  It also returns its own Scatter and Chase targets.
 */

class Inky : public Enemy
{
    public:
        typedef shared_ptr<sf::Texture> texturePtr; /**< \typedef for a shared pointer to an sf::Texture */
        typedef Enemy* enemyPtr; /**< \typedef for a pointer to an Enemy */
        typedef Player* playerPtr; /**< \typedef for a pointer to a Player, to improve readability */

        /** \brief Default Constructor for Inky */
        Inky ():Enemy(){}

        /** \brief Constructor for Inky with initialisation list
         *
         *  Constructs an Enemy object and initialises the default direction to UP
         *
         *  \param textures, a map<string,texturePtr> which maps a label to a texture pointer
         *  \param position, an sf::Vector2f which contains the x and y coordinates of the
         *      default and initial position of Inky
         *  \param player, a pointer to the Player
         *  \param maze, a pointer to the Maze
         *  \param blinky, a pointer to Blinky
         */
        Inky(map<string,texturePtr> textures, sf::Vector2f position, playerPtr player, mazePtr maze, enemyPtr blinky);

        /** \brief Handles Inky's state changes, as well as calls on the current state to update
         *
         *  First any state changes are handled and updated using inherited functionality.
         *  After this, the currrent state's update function is called, passing in the time
         *  increment dt.
         *
         *  If the state stack is empty, a Scatter State is added to it
         *
         *  \param dt, the time increment since the last call to update
         */
        void update(float dt) override;

        /** \brief Returns the chase target for Inky
         *
         *  Returns Inky's chase target. This is defined as taking the vector between
         *  the tile which is two tiles ahead of Player and Blinky's current tile,
         *  and then rotating this vector by 180 degrees.
         *
         *  \returns An sf::Vector2f in the form {x,y}, giving the x and y coordinates of the
         *  Inky's chase target.
         */
        sf::Vector2f getChaseTarget() override;

        /** \brief Returns the scatter target for Inky
         *
         *  Returns Inky's scatter target, which is defined as the centre of
         *  the bottom-left tile of the Maze.
         *
         *  \returns An sf::Vector2f in the form {x,y}, giving the x and y coordinates of the
         *  centre of the bottom-left tile of the Maze.
         */
        sf::Vector2f getScatterTarget() override;

    protected:

    private:
        enemyPtr blinky_;
};

#endif // INKY_H
