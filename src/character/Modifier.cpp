#include "character/Modifier.hpp"
#include "resources/ResourceDefs.hpp"
#include "Errors.hpp"
#include <cstring>
#include <tuple>

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

void Modifier::setDescription(const string& desc){
  _description = desc;
}

const string& Modifier::getDescription() const{
  return _description;
}

DEF_XML_RESOURCE_LOAD(Modifier){
  if( strcmp(node->name(),"modifier") != 0 )
    raise(MalformedResourceException,path,string("Expected 'modifier' node but found '")+node->name()+"'.");

  list<tuple<Stats::Stat,int>> statsAndValues;
  for(XmlNode* child = node->first_node(); child; child = child->next_sibling()){
    //skip non stat nodes
    if( strcmp(node->name(),"stat") != 0 ){
      string name = "";
      string value = "";
      for(XmlAttribute* attr = child->first_attribute(); attr; attr = attr->next_attribute()){
        if( strcmp(attr->name(), "name") == 0 ){
          name = attr->value(); 
        }else if( strcmp(attr->name(), "value") == 0 ){
          value = attr->value(); 
        }
      }

      Stats::Stat stat;
      //sanity checks
      if( name == "" )
        raise(MalformedResourceException,path,string("'name' attribute required in 'stat' node"));
      if( value == "" )
        raise(MalformedResourceException,path,string("'value' attribute required in 'stat' node"));
      if( !Stats::getStatForString(name,&stat) ) //also fill in the correct value for stat
        raise(MalformedResourceException,path,string("Invalide stat '"+name+"'"));

      //save the value for later
      statsAndValues.push_back(make_tuple(stat,atoi(value.c_str())));
    }
  }//exited loop = no errors

  Modifier* mod = new Modifier("");
  for( auto t : statsAndValues ){
    mod->setValueFor(get<0>(t),get<1>(t));
  }
  
  return mod;
}

