#include "scripting/EventRaiser.hpp"
#include "scripting/EventManager.hpp"

void EventRaiser::raiseEvent(GenericEvent* type){
  EventManager::global()->raise(this->getPath(),type);
}

