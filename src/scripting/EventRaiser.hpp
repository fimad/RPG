#ifndef _EVENT_RAISER_HPP_
#define _EVENT_RAISER_HPP_

#include "resources/Path.hpp"

class GenericEvent;
class EventRaiser {
  public:
    virtual const Path& getPath() = 0;
    void raiseEvent(GenericEvent* type);
};

#endif

