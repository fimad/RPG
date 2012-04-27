#include "character/Race.hpp"
#include "character/Modifier.hpp"
#include <cstring>

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

DEF_XML_RESOURCE_LOAD(Race){
  if( strcmp(node->name(),"race") != 0 )
    raise(MalformedResourceException,path,string("Expected 'race' node but found '")+node->name()+"'.");

  //value loading loop
  string name="";
  string desc="";
  Modifier* mod=NULL;
  for(XmlNode* child = node->first_node(); child; child = child->next_sibling()){
    if( strcmp(child->name(),"name") == 0 ){
      name = child->value();
    }else if( strcmp(child->name(),"description") == 0 ){
      desc = child->value();
    }else if( strcmp(child->name(),"modifier") == 0 ){
      mod = XmlResource::load<Modifier>(path,child);
    }
  }

  //sanity checks
  if( name=="" )
    raise(MalformedResourceException,path,string("No name supplied in race definition."));
  if( desc=="" )
    raise(MalformedResourceException,path,string("No description supplied in race definition."));
  if( mod==NULL )
    raise(MalformedResourceException,path,string("No modifier supplied in race definition."));

  return new Race(name,desc,mod);
}

