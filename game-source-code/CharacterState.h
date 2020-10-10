#ifndef CHARACTER_STATE_H
#define CHARACTER_STATE_H

/** \file Character.h
    \brief Contains the class definition for an abstract "Character State" class, which will be inherited by
    all character states
*/

/** \class CharacterState
 *  \brief Base class for character states
 *
 *  This class is a base class which will be inherited by multiple
 *  character states. It is a purely abstract class which has no members
 *  or implementation of its own, but the interface is inherited by its
 *  derived classes.
 *
 *  Within every state, a character will have a certain behaviour, which is
 *  defined by the state. This base class provides a means of doing that via
 *  polymorphism - every state can be referred to as a CharacterState object,
 *  and the update and enter functions can be called on them.
 */
class CharacterState
{
public:

    /** \brief Default constructor */
    CharacterState() {};

    /** \brief Default destructor */
    virtual ~CharacterState() {};

    /** Abstract function for state specific update behaviour*/
    virtual void update(float dt) = 0;
    /** Abstract function for state specific entrance behaviour*/
    virtual void enter() = 0;

private:

};

#endif
