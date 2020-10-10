#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

/// \file StateMachine.h
/// \brief Contains the class definition for the "StateMachine" class

#include "State.h"

#include <memory>
#include <stack>

using namespace std;


typedef unique_ptr<State> statePtr; /**\typedef a unique pointer to the Game structure, to improve readability */

/// \class StateMachine
/// \brief This class manages the changes in he game's states and keeps track of the current state
///
/// State machine pushes states onto, and pops states off of a stack when requested to do so by the states themselves. This class exists so that states can be succesfully removed before new states are added, as it is not desireable for states to remove themselves. The current state can also be provided at any time so that the game loop can delegate to it appropriately.

class StateMachine
{
public:
    
    /// Constructor
    StateMachine() {}
    
    /// Destructor
    ~StateMachine() {}
    
    /// Add a new state to the stack, which is set to become the current state.
    ///
    /// This state will become the new current state in the following cycle of the game loop. The user can specify whether the old state should be removed before adding the new state or keeping the it on the stack so as to return to it later
    /// @param newState a unique pointer to the new state
    /// @param isReplacing a boolean that is true if the old state should be removed, and false if it should not
    void addState(statePtr newState, bool isReplacing = true);
    
    /// Set the current state tobe removed
    void removeState();
    
    /// Add or remove the current state according to the boolean flags set by addState() and removeState()
    void handleStateChange();
    
    /// Get a pointer to the current state
    /// \return a reference to a unique pointer that points to the current state
    statePtr& getCurrentState() {return states_.top();}

private:
    stack<statePtr> states_;
    
    statePtr newState_;
    
    bool isAdding_;
    bool isRemoving_;
    bool isReplacing_;
};

#endif
