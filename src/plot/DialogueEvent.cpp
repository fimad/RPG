#include "plot/DialogueEvent.hpp"

DialogueEvent::DialogueEvent(const string& value){
  this->_value = value;
}

const string& DialogueEvent::value(){
  return _value;
}

bool DialogueEvent::equals(const GenericEvent* gevent){
  event_test_and_set(const DialogueEvent*,other,gevent);
  return this->_value == other->_value;
}

