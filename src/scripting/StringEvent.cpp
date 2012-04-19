#include "scripting/StringEvent.hpp"

StringEvent::StringEvent(const string& value){
  this->_value = value;
}

const string& StringEvent::value(){
  return _value;
}

bool StringEvent::equals(const GenericEvent* gevent){
  event_test_and_set(const StringEvent*,other,gevent);
  return this->_value == other->_value;
}

