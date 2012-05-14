#include "character/Spell.hpp"
#include "scripting/LuaWrapper.hpp"

Spell::Spell(const string& name, const string& description, const string& effect)
  : _name(name)
  , _description(description)
  , _effect(LuaWrapper::makeLuaFunc<int,Character*,Tile*>(effect))
{}

const string& Spell::getName(){
  return _name;
}

const string& Spell::getDescription(){
  return _description;
}

int Spell::cast(Character* caster,Tile* target){
  return _effect(caster,target);
}

DEF_XML_RESOURCE_LOAD(Spell){
  if( strcmp(node->name(),"spell") != 0 )
    raise(MalformedResourceException,path,string("Expected 'spell' node but found '")+node->name()+"'.");

  string name = "";
  string description = "";
  string effect = "";

  //value setting loop
  for(XmlNode* child = node->first_node(); child; child = child->next_sibling()){
    if( strcmp(child->name(),"name") == 0 )
      name = child->value();
    if( strcmp(child->name(),"description") == 0 )
      description = child->value();
    if( strcmp(child->name(),"lua") == 0 )
      effect = *(XmlResource::load<LuaWrapper::LuaSrc>(path,child,manager));
  }

  //sanity checks
  if( name == "" )
    raise(MalformedResourceException,path,"Spells require a name.");
  if( description == "" )
    raise(MalformedResourceException,path,"Spells require a description.");
  if( effect == "" )
    raise(MalformedResourceException,path,"Spells require an effect function.");

  Spell* spell = new Spell(name,description,effect);

  return spell;
}

