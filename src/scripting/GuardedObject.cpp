#include "scripting/GuardedObject.hpp"

GuardedObject::GuardedObject(const Condition& condition) : _condition(condition){
}

bool GuardedObject::isAllowed(){
  return _condition.allows();
}

void GuardedObject::setCondition(const Condition& condition){
  _condition = condition;
}

Condition& GuardedObject::getCondition(){
  return _condition;
}

