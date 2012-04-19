#include "scripting/StringEvent.hpp"

StringEvent::StringEvent(const string& value){
  this->value = value;
}

bool StringEvent::equals(const GenericEvent* gevent){
  event_test_and_set(const StringEvent*,other,gevent);
  return this->value == other->value;
}

