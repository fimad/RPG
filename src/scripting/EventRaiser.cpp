#include "scripting/EventRaiser.hpp"
#include "scripting/EventManager.hpp"

void EventRaiser::raiseEvent(GenericEvent* type){
  EventManager::global()->raiseEvent(this->getPath(),type);
}

