#ifndef BLINKY_H
#define BLINKY_H

/** \file Blinky.h
 *  \brief Contains the class definition of Blinky, derived from Enemy
 */

#include "Enemy.h"
#include "Player.h"

/** \class Blinky
 *  \brief One of the four derived Enemy classes
 *
 *  Each enemy derived class has distinct behaviour. This class manages its own states,
 *  as well as delegates its update functionality to its current state.
 *
 *  It also returns its own Scatter and Chase targets.
 */

class Blinky : public Enemy
{
    public:
        typedef shared_ptr<sf::Texture> texturePtr; /**< \typedef for a shared pointer to an sf::Texture */

        /** \brief Default Constructor for Blinky */
        Blinky ():Enemy(){}

        /** \brief Constructor for Blinky with initialisation list
         *
         *  Constructs an Enemy object and sets the default direction to RIGHT
         *
         *  \param textures, a map<string,texturePtr> which maps a label to a texture pointer
         *  \param position, an sf::Vector2f which contains the x and y coordinates of the
         *      default and initial position of Blinky
         *  \param player, a pointer to the Player
         *  \param maze, a pointer to the Maze
         */
        Blinky(map<string,texturePtr> textures, sf::Vector2f position, playerPtr player, mazePtr maze);

        /** \brief Handles state changes, as well as calls on the current state to update
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

        /** \brief Returns the chase target for Blinky
         *
         *  Returns Blinky's chase target, which is defined as the Player's
         *  current tile.
         *
         *  \returns An sf::Vector2f in the form {x,y}, giving the x and y coordinates of the
         *  Blinky's chase target.
         */
        sf::Vector2f getChaseTarget() override;

        /** \brief Returns the scatter target for Blinky
         *
         *  Returns Blinky's scatter target, which is defined as the centre of
         *  the top-left tile of the Maze.
         *
         *  \returns An sf::Vector2f in the form {x,y}, giving the x and y coordinates of the
         *  centre of the top-left tile of the Maze.
         */
        sf::Vector2f getScatterTarget() override;

    protected:

    private:

};

#endif // BLINKY_H
