#ifndef _STRING_EVENT_HPP_
#define _STRING_EVENT_HPP_

#include <string>
#include "scripting/GenericEvent.hpp"
using namespace std;

class StringEvent : public GenericEvent {
  public:
    StringEvent(const string& value);
    virtual bool operator==(const GenericEvent&);
  private:
    string value;
};

#endif

