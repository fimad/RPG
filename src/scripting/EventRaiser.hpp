#ifndef _STRING_EVENT_HPP_
#define _STRING_EVENT_HPP_

#include "resources/Path.hpp"

class GenericEvent;
class EventRaiser {
  public:
    virtual const Path& getPath() = 0;
    void raiseEvent(GenericEvent* type);
};

#endif

