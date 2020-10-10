#ifndef SUBJECT_H
#define SUBJECT_H

/** \file Subject.h
 *  \brief Contains the class definition of the Subject
 */

#include "Observer.h"
#include <vector>
#include <memory>

/** \class Subject
 *
 *  The Subject class forms part of the observer Pattern, along with the Observer class.
 *  Classes which inherit Subject will be able to be under observation, and notify
 *  observers of important events.
 */
using namespace std;

class Subject
{
public:
    /** \brief Adds an observer to the list of observers
     *
     *  Adds an observer to the internally stored list of observers, so
     *  that the observer will receive notifications.
     *
     *  \param observer, a pointer to the observer object to be added
     */
    void addObserver(Observer* observer);

    /** \brief Removes an observer from the list of observers
     *
     *  Removes an observer from the internally stored list of observers, so
     *  the observer will no longer receive notifications.
     *
     *  \param observer, a pointer to the observer object to be removed
     */
    void removeObserver(Observer* observer);

protected:
    void notify(Observer::Event event);

private:
    vector<Observer*> observers_;   // Change to smart pointer

};

#endif
