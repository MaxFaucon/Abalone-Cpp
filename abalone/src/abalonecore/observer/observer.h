#ifndef __OBSERVER__H__
#define __OBSERVER__H__

#include "model/board.h"

/**
 * @brief The Observer class Basic abstract class of any observer.
 */
class Observer
{
  public:

    virtual ~Observer() = default;

    /**
     * @brief Virtual method that each observer must implement. It's this
     * method that the observed subject calls when there is a notification.
     * @param propertyName A string that allows the observer to know what
     * has been modified in the subject.
     */
    virtual void update(const std::string & propertyName) = 0;
};

#endif
