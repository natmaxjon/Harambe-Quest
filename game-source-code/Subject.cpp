#include "Subject.h"

#include <algorithm>

void Subject::addObserver(Observer* observer)
{
    observers_.push_back(observer);
}

void Subject::removeObserver(Observer* observer)
{
    observers_.erase(remove(observers_.begin(), observers_.end(), observer), observers_.end());
}

void Subject::notify(Observer::Event event)
{
    for (auto observer : observers_)
    {
        observer->onNotify(event);
    }
}
