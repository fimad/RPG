#ifndef _STRING_EVENT_HPP_
#define _STRING_EVENT_HPP_

#include <string>
#include "scripting/GenericEvent.hpp"
using namespace std;

class StringEvent : public GenericEvent {
  public:
    StringEvent(const string& value);
    virtual bool equals(const GenericEvent*);
    const string& value();
  private:
    string _value;
};

#endif

