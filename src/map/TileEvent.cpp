#include "map/TileEvent.hpp"

TileEvent::TileEvent(Character* character, const string& value)
  : _value(value)
  , _character(character)
{
}

TileEvent::TileEvent(const TileEvent& event)
  : _value(event._value)
  , _character(event._character)
{
}

bool TileEvent::equals(const GenericEvent* gevent){
  event_test_and_set(const TileEvent*,other,gevent);
  return this->_value == other->_value;
}

void TileEvent::setCharacter(Character* character){
  _character = character;
}

const string& TileEvent::value(){
  return _value;
}

Character* TileEvent::getCharacter(){
  return _character;
}

