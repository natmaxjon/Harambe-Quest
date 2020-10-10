#include "StateMachine.h"

void StateMachine::addState(statePtr newState, bool isReplacing)
{
    isAdding_ = true;
    isReplacing_ = isReplacing;
    newState_ = move(newState);
}

void StateMachine::removeState()
{
    isRemoving_ = true;
}

void StateMachine::handleStateChange()
{
    if (isRemoving_ && !states_.empty())    // Can this logic can be refactored? It's quite nested
    {                                       // Maybe split into helper functions?
        states_.pop();

        // If it's STILL not empty
        if (!states_.empty())
        {
            states_.top()->resume();
        }

        isRemoving_ = false;
    }

    if (isAdding_)
    {
        if (!states_.empty())
        {
            if (isReplacing_)
            {
                states_.pop();
            }
            else
            {
                states_.top()->pause();
            }
        }

        states_.push(move(newState_));
        states_.top()->initialise();
        isAdding_ = false;
    }
}
