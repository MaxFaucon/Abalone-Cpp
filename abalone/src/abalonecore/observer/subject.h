#ifndef __SUBJECT__H__
#define __SUBJECT__H__

#include <set>
#include "model/board.h"

class Observer;

/**
 * @brief The Subject class Basic class of all observable subjects.
 */
class Subject
{
public:
    virtual ~Subject() = default;

    /**
     * @brief A method that warns the observers of a change of state of the
     * subject of observation, by invoking their method Observer::update().
     * @param propertyName A string that allows the observer to know what
     * has been modified in the subject.
     */
    void notifyObservers(const std::string & propertyName = "No property") const;

    /**
     * @brief addObserver Inline method allowing an observer to record himself as
     * listener of the subject of observation.
     * @param observer A pointer to the observer.
     */
    inline void addObserver(Observer * observer);

private:
    std::set<Observer *> m_observers { };

};

void Subject::addObserver(Observer *observer)
{        
    m_observers.insert(observer);
}

#endif

