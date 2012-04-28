#include "map/MapContents.hpp"
#include "character/Character.hpp"
#include "resources/ResourceManager.hpp"
#include "map/Map.hpp"
#include <cstring>
#include <string>

MapContents::MapContents(set<tuple<int,int,Character*>> characters)
  : _characters(characters)
{}

void MapContents::fill(Map* map){
  //place characters
  for(auto t : _characters){
    map->addCharacterAt(get<0>(t),get<1>(t),get<2>(t));
  }
}

DEF_XML_RESOURCE_LOAD(MapContents){
  if( strcmp(node->name(),"contents") != 0 )
    raise(MalformedResourceException,path,string("Expected 'contents' node but found '")+node->name()+"'.");

  set<tuple<int,int,Character*>> characters;

  for(XmlNode* child=node->first_node(); child; child=child->next_sibling()){
    if( strcmp("character",child->name())==0 ){
      int x=-1;
      int y=-1;
      Character* c=NULL;
      string path="";
      for(XmlAttribute* attr=child->first_attribute(); attr; attr=attr->next_attribute()){
        if( strcmp("x",attr->name())==0 ){
          x = atoi(attr->value());
        }else if( strcmp("y",attr->name())==0 ){
          y = atoi(attr->value());
        }else if( strcmp("path",attr->name())==0 ){
          path = attr->value();
        }
      }

      //error checking
      if( x<0 || y<0 ){
        for(auto c : characters) delete get<2>(c);
        raise(MalformedResourceException,path,"X and Y value needed for object");
      }
      if( path=="" ){
        for(auto c : characters) delete get<2>(c);
        raise(MalformedResourceException,path,"Path needed for object");
      }

      //try to load the character and fail gracefully
      try{
        c = manager->loadResource<Character>(Path(path));
      }catch(Exception& e){
        for(auto c : characters) delete get<2>(c);
        throw e;
      }

      //add it to the set
      characters.insert(make_tuple(x,y,c));
    }
  }

  return new MapContents(characters);
}

