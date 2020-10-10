#ifndef OBSERVER_H
#define OBSERVER_H
/** \file Observer.h
 *  \brief Contains the class definition of the Observer
 */

/** \class Observer
 *
 *  The Observer class forms part of the observer Pattern, along with the Subject class.
 *  Classes which inherit the Observer will be able to observe and be notified of
 *  important events from subjects they observe.
 */
class Observer
{
public:
    // Valid events
    /** \enum A list of valid events */
    enum class Event
    {
        FRUIT_EATEN,
        POWER_PELLET_EATEN,
        SUPER_PELLET_EATEN,
        GHOST_EATEN,
        KEY_EATEN,
        GATE_BROKEN,
        LIFE_LOST
    };

    /** \brief Observer class destructor */
    virtual ~Observer() {};

    /** \brief Abstract function for Observer dependent functionality
     *
     *  Every observer will implement this function and act on whichever
     *  events the observer feels is important.
     *
     *  \param event, the event which the subject sent a notification of
     */
    virtual void onNotify(Event event) = 0;
};

#endif
