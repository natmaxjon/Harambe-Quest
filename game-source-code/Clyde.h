#ifndef CLYDE_H
#define CLYDE_H

/** \file Clyde.h
 *  \brief Contains the class definition of Clyde, derived from Enemy
 */

#include "Enemy.h"
#include "Player.h"

/** \class Clyde
 *  \brief One of the four derived Enemy classes
 *
 *  Each enemy derived class has distinct behaviour. This class manages its own states,
 *  as well as delegates its update functionality to its current state.
 *
 *  It also returns its own Scatter and Chase targets.
 */
class Clyde : public Enemy
{
     public:
        typedef shared_ptr<sf::Texture> texturePtr; /**< \typedef for a shared pointer to an sf::Texture */

        /** \brief Default Constructor for Clyde */
        Clyde ():Enemy(){}

        /** \brief Constructor for Clyde with initialisation list
         *
         *  Constructs an Enemy object and initialises the default direction to LEFT
         *
         *  \param textures, a map<string,texturePtr> which maps a label to a texture pointer
         *  \param position, an sf::Vector2f which contains the x and y coordinates of the
         *      default and initial position of Clyde
         *  \param player, a pointer to the Player
         *  \param maze, a pointer to the Maze
         */
        Clyde(map<string,texturePtr> textures, sf::Vector2f position, playerPtr player, mazePtr maze);


         /** \brief Handles Clyde's state changes, as well as calls on the current state to update
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

        /** \brief Returns the chase target for Clyde
         *
         *  Returns Clyde's chase target, which is Player's current tile
         *  if the distance between Clyde and the Player is less than eight tiles,
         *  or his scatter target otherwise
         *
         *  \returns An sf::Vector2f in the form {x,y}, giving the x and y coordinates of the
         *  Clyde's chase target.
         */
        sf::Vector2f getChaseTarget() override;

        /** \brief Returns the scatter target for Clyde
         *
         *  Returns Clyde's scatter target, which is defined as the centre of
         *  the bottom-right tile of the Maze.
         *
         *  \returns An sf::Vector2f in the form {x,y}, giving the x and y coordinates of the
         *  centre of the bottom-right tile of the Maze.
         */
        sf::Vector2f getScatterTarget() override;

    protected:

    private:

};

#endif // CLYDE_H
