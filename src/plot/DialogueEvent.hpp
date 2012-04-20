#ifndef _DIALOGUE_EVENT_HPP_
#define _DIALOGUE_EVENT_HPP_

#include <string>
#include "scripting/GenericEvent.hpp"
using namespace std;

class DialogueEvent : public GenericEvent{
  public:
    DialogueEvent(const string& value);
    virtual bool equals(const GenericEvent*);
    const string& value();
  private:
    string _value;
};

#endif

