#ifndef GAME_LOOP_H
#define GAME_LOOP_H

/// \file GameLoop.h
/// \brief Contains the class definition for the "GameLoop" class

#include <SFML/Graphics.hpp>

#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

#include <memory>

using namespace std;

/// \class GameLoop
/// \brief This class implements the overarching structure for the entire program
///
/// Each loop of the game consists of four major steps: handling state changes, handling user input for the current state, updating the private members of the current state, and displaying them onto the screen. The elapsed time between loops is also monitored to ensure that the game objects are updated according to the real time elapsed and not the clock speed of the machine running the game

/// \struct A structure containing the core elements of the game. Namely: The state machine, asset manager, input manager and the game window
struct Game
{
    StateMachine stateMachine;
    AssetManager assetManager;
    InputManager inputManager;
    sf::RenderWindow window;
};

typedef shared_ptr<Game> gamePtr; /**\typedef a shared pointer to the Game structure, to improve readability */

class GameLoop
{
public:
    
    /// Constructor
    /// @param width width of the game screen (pixels)
    /// @param height heght of the game screen (pixels)
    /// @param title title of the window
    /// @param style style of the window
    GameLoop(float width, float height, const string& title, sf::Uint32 style);
    
    /// Begin the game loop
    ///
    /// Each loop handles any state changes and user inputs, updates the current state's private members and displays them on the game screen for the user to see
    void run();

private:
    sf::Clock clock_;
    gamePtr game_ = make_shared<Game>();
    
    float previousTime_ = 0.0f;
    float currentTime_ = 0.0f;
    float elapsedTime_ = 0.0f;
    float lag_ = 0.0f;
};

#endif
