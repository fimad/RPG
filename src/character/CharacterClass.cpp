#include "character/CharacterClass.hpp"
#include "character/ProxyModifier.hpp"
#include <algorithm>
#include <cstring>

CharacterClass::CharacterClass(const string& name, const string& desc, const list<Modifier*> modifiers, int level)
  : _name(name)
  , _description(desc)
  , _modifiers(modifiers.begin(),modifiers.end())
{
  _proxyModifier = new ProxyModifier(_name+" class modifier",_modifiers[0]);
  setLevel(level);
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
  _proxyModifier->setModifier(_modifiers[_currentLevel-1]);
}

void CharacterClass::levelUp(){
  setLevel(_currentLevel+1);
}

bool CharacterClass::canLevelUp(){
  return _currentLevel < maxLevel();
}

int CharacterClass::currentLevel(){
  return _currentLevel;
}

int CharacterClass::maxLevel(){
  return _modifiers.size();
}

DEF_XML_RESOURCE_LOAD(CharacterClass){
  if( strcmp(node->name(),"class") != 0 )
    raise(MalformedResourceException,path,string("Expected 'class' node but found '")+node->name()+"'.");

  //value loading loop
  string name="";
  string desc="";
  XmlNode* levels = NULL;
  list<Modifier*> mods;
  for(XmlNode* child = node->first_node(); child; child = child->next_sibling()){
    if( strcmp(child->name(),"name") == 0 ){
      name = child->value();
    }else if( strcmp(child->name(),"description") == 0 ){
      desc = child->value();
    }else if( strcmp(child->name(),"levels") == 0 ){
      levels = child;
    }
  }

  //load each level
  if(levels){
    for(XmlNode* child = levels->first_node(); child; child = child->next_sibling()){
      if( strcmp(child->name(), "level") == 0
        && child->first_node()
        && strcmp(child->first_node()->name(), "modifier") == 0){
        mods.push_back(XmlResource::load<Modifier>(path,child->first_node()));
      }
    }
  }

  //sanity checks
  if( name=="" )
    raise(MalformedResourceException,path,string("No name supplied in race definition."));
  if( desc=="" )
    raise(MalformedResourceException,path,string("No description supplied in race definition."));
  if( mods.size()==0 )
    raise(MalformedResourceException,path,string("At least one level definition must be supplied."));

  return new CharacterClass(name,desc,mods);
}

