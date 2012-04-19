#ifndef _GUARDED_OBJECT_HPP_
#define _GUARDED_OBJECT_HPP_

#include "scripting/Condition.hpp"

class GuardedObject{
  public:
    GuardedObject(const Condition& condition = Condition::AlwaysAllow);
    bool isAllowed();
    void setCondition(const Condition& condition);
    Condition& getCondition();
  private:
    Condition _condition;
};

#endif

