#include "observer/observer.h"
#include "observer/subject.h"
#include "model/game.h"
#include <string>

void Subject::notifyObservers(const std::string  & propertyName) const
{
    for (Observer * observer : m_observers)
    {
        observer->update(propertyName);
    }
}
