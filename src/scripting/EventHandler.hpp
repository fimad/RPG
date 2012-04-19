#ifndef _EVENT_HANDLER_HPP_
#define _EVENT_HANDLER_HPP_

#include "resources/Path.hpp"

class GenericEvent;
class EventHandler{
  public:
    virtual void handleEvent(Path raiser, GenericEvent* type) = 0;
};

#endif

