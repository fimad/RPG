#include "character/Race.hpp"

Race::Race(const string& name, const string& description, Modifier* modifier)
  : _name(name)
  , _description(description)
  , _modifier(modifier)
{
}

Race::~Race(){
  delete _modifier;
}

//TODO:when attribute api is decided, fill this in
Modifier* Race::getModifier() const{
  return _modifier;
}

const string& Race::getName() const{
  return _name;
}

const string& Race::getDescription() const{
  return _description;
}

//TODO: load race xml
DEF_XML_RESOURCE_LOAD(Race){
  return NULL;
}

