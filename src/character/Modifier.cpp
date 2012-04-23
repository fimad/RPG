#include "character/Modifier.hpp"

Modifier::Modifier(const string& description)
  : _description(description)
{
}

Modifier::~Modifier(){
}

int Modifier::valueFor(Stats::Stat stat){
  return (_values.count(stat)) ? _values[stat] : 0;
}

void Modifier::setValueFor(Stats::Stat stat, int value){
  _values[stat] = value;
}

const string& Modifier::getDescription() const{
  return _description;
}

//TODO: xml load Modifier
DEF_XML_RESOURCE_LOAD(Modifier){
  return NULL;
}

