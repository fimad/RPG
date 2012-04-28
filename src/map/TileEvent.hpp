#ifndef _TILE_EVENT_HPP_
#define _TILE_EVENT_HPP_

#include <string>
#include "scripting/GenericEvent.hpp"
using namespace std;

class Character;

//equivalence is based only on the string value
class TileEvent : public GenericEvent{
  public:
    TileEvent(Character* character, const string& value);
    TileEvent(const TileEvent& event);
    virtual bool equals(const GenericEvent*);
    void setCharacter(Character* character);
    const string& value();
    Character* getCharacter();
  private:
    string _value;
    Character* _character;
};

#endif

