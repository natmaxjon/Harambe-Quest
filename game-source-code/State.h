#ifndef STATE_H
#define STATE_H

/// \file State.h
/// \brief Contains the class definition for the "State" class

/// \class State
/// \brief The base class that all state types must inherit
///
/// This class provides the interface that all states must conform to. Specifically, each state must have a method for initialisation, processing input, updating its private members, and rendering them to the screen

class State
{
public:
    /// Default constructor
    State() {};
    
    /// Destructor
    virtual ~State() {};
    
    /// Initialise the current state
    virtual void initialise() = 0;
    
    /// Process user input
    virtual void processInput() = 0;
    
    /// Update private data members
    /// @param dt the elapsed time in milliseconds
    virtual void update(float dt) = 0;
    
    /// Render drawables to the game screen
    /// @param dt the elapsed time in milliseconds
    virtual void draw(float dt) = 0;
    
    /// Pause the current state
    virtual void pause() {};
    
    /// Resume the current state
    virtual void resume() {};

private:

};

#endif
