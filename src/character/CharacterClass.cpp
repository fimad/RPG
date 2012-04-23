#include "character/CharacterClass.hpp"
#include "character/ProxyModifier.hpp"
#include <algorithm>

CharacterClass::CharacterClass(const string& name, const string& desc, const list<Modifier*> modifiers, int level)
  : _name(name)
  , _description(desc)
  , _modifiers(modifiers.begin(),modifiers.end())
{
  setLevel(level);
  _proxyModifier = new ProxyModifier(_name+" class modifier",_modifiers[_currentLevel-1]);
}

CharacterClass::~CharacterClass(){
  delete _proxyModifier;
  for(Modifier* m : _modifiers){
    delete m;
  }
}

const string& CharacterClass::getName() const{
  return _name;
}

const string& CharacterClass::getDescription() const{
  return _description;
}

Modifier* CharacterClass::getModifier() const{
  return _proxyModifier;
}

void CharacterClass::setLevel(int level){
  _currentLevel = max(1,min(level,maxLevel()));
}

void CharacterClass::levelUp(){
  setLevel(_currentLevel+1);
}

bool CharacterClass::canLevelUp(){
  return _currentLevel < maxLevel();
}

int CharacterClass::maxLevel(){
  return _modifiers.size();
}

//TODO:CharacterClass xml load
DEF_XML_RESOURCE_LOAD(CharacterClass){
  return NULL;
}

