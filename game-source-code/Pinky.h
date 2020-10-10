#ifndef PINKY_H
#define PINKY_H
/** \file Pinky.h
 *  \brief Contains the class definition of Pinky, derived from Enemy
 */
#include "Enemy.h"

/** \class Pinky
 *  \brief One of the four derived Enemy classes
 *
 *  Each enemy derived class has distinct behaviour. This class manages its own states,
 *  as well as delegates its update functionality to its current state.
 *
 *  It also returns its own Scatter and Chase targets.
 */
class Pinky : public Enemy
{
     public:
        typedef shared_ptr<sf::Texture> texturePtr; /**< \typedef for a shared pointer to an sf::Texture */

        /** \brief Default Constructor for Pinky */
        Pinky ():Enemy(){}

        /** \brief Constructor for Pinky with initialisation list
         *
         *  Constructs an Enemy object and initialises the default direction to DOWN
         *
         *  \param textures, a map<string,texturePtr> which maps a label to a texture pointer
         *  \param position, an sf::Vector2f which contains the x and y coordinates of the
         *      default and initial position of Pinky
         *  \param player, a pointer to the Player
         *  \param maze, a pointer to the Maze
         */
        Pinky(map<string,texturePtr> textures, sf::Vector2f position, playerPtr player, mazePtr maze) :
         Enemy(textures, position, player, maze)
         {current_dir_ = DOWN;
         default_dir_ = DOWN;}

        /** \brief Handles Pinky's state changes, as well as calls on the current state to update
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

        /** \brief Returns the chase target for Pinky
         *
         *  Returns Pinky's chase target, which is defined as being four tiles
         *  ahead of Player's current tile, in Player's current direction.
         *
         *  \returns An sf::Vector2f in the form {x,y}, giving the x and y coordinates of the
         *  Pinky's chase target.
         */
        sf::Vector2f getChaseTarget() override;

        /** \brief Returns the scatter target for Pinky
         *
         *  Returns Pinky's scatter target, which is defined as the centre of
         *  the top-right tile of the Maze.
         *
         *  \returns An sf::Vector2f in the form {x,y}, giving the x and y coordinates of the
         *  centre of the top-right tile of the Maze.
         */
        sf::Vector2f getScatterTarget() override;

    protected:

    private:
};

#endif // Inky_H
