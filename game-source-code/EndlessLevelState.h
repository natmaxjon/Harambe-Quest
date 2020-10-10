#ifndef ENDLESS_LEVEL_STATE_H
#define ENDLESS_LEVEL_STATE_H
/** \file EndlessLevelState.h
 *  \brief File containing the endless level state
 */
#include <SFML/Graphics.hpp>

#include "State.h"
#include "GameLoop.h"

#include "Player.h"
#include "Enemy.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"
#include "Maze.h"

#include "Scoreboard.h"
#include "Soundboard.h"

/** \class EndlessLevelState
 *  \brief A state which encapsulates the actual game in its entirety
 *
 *  This state is the most important for the game itself, since it stores the
 *  game objects, and runs a single level of the game, which can be played
 *  an endless amount of times.
 */

class EndlessLevelState: public State
{
public:
    typedef std::shared_ptr<sf::Texture> texturePtr; /**< Alias for a shared pointer to sf::Texture */

    /** \brief EndlessLevelState Constructor
     *
     *  Constructs the endless level state and initialises member variables.
     *  The level number, lvlNumber, defaults to 1 if no value is provided.
     *
     *  \param game, a pointer to the game object
     *  \param mazeName, the name of the maze currently being played
     *  \param lvlNumber, the current level number
     */
    EndlessLevelState(gamePtr game, string mazeName, int lvlNumber = 1);

    /** \brief Private members are initialised
     *
     *  The maze is loaded and constructed and the characters are loaded and constructed as well.
     *  The score, scoreboard, soundboard and number of lives are initialised as well.
     *
     *  All loading takes place via the Asset Manager.
     */
    void initialise() override;

    /** \brief Input from the keyboard is processed
     *
     *  An exit request or key press is detected and action taken, such as moving the
     *  player.
     */
    void processInput() override;

    /** \brief Private members are updated
     *
     *  The maze, characters, and score is updated. Interactions between the player and
     *  enemies are evaluated. Additionally, win and lose conditions are checked, leading
     *  to an intermediate state if the maze is clear, or a game over state if the players
     *  lives are finished.
     */
    void update(float dt) override;

    /** \brief All maze, character and score drawable objects are drawn
     *
     *  First the background is drawn, then the maze, then the characters, and finally
     *  the score, maze title and number of lives left.
     */
    void draw(float dt) override;

private:
    gamePtr game_;
    string mazeName_;
    int lvlNumber_;
    sf::Clock clock_;

    Maze maze_;
    vector<sf::Vector2f> nodes_;

    Scoreboard scoreBoard_;
    Soundboard soundBoard_;

    int songNumber = 0;

    Player player_;
    Blinky blinky_;
    Inky inky_;
    Pinky pinky_;
    Clyde clyde_;

    sf::Text scoreText_;
    sf::Text mazeHeading_;
    sf::Sprite life_;
    sf::Sprite background_;
    sf::Texture bgTexture_;

    vector<sf::Sprite> livesCounter_;

    // Private helper functions
    void loadMaze(AssetManager& assetManager);
    void loadCharacters(AssetManager& assetManager);
    void loadInfoBar(AssetManager& assetManager);
    void PlayerEnemyInteraction(Enemy& enemy);
    void resetCharacters();
    void updateInfoBar();
};

#endif
