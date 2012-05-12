#include "map/Tile.hpp"
#include "map/Map.hpp"
#include "map/TileEvent.hpp"
#include "scripting/GenericEvent.hpp"
#include "resources/ResourceManager.hpp"
#include "character/Character.hpp"
#include <cstring>

#include <iostream>
using namespace std;

Tile::Tile(Map* map, int x, int y, bool walkable, char symbol, TileEvent* walkEvent, Map* subMap)
  : _map(map)
  , _walkable(walkable)
  , _walkEvent(walkEvent)
  , _x(x)
  , _y(y)
  , _subMap(subMap)
  , _symbol(symbol)
{
  _occupant = NULL;
}

Tile::~Tile(){
  if(_subMap)
    delete _subMap;
  if(_walkEvent)
    delete _walkEvent;
}

bool Tile::isPortal() const{
  return _subMap != NULL;
}

bool Tile::isWalkable() const{
  return _walkable && _occupant == NULL;
}

bool Tile::hasOccupant() const{
  return _occupant != NULL;
}

Character* Tile::getOccupant() const{
  return _occupant;
}

Map* Tile::getSubMap() const{
  return _subMap;
}

Map* Tile::getMap() const{
  return _map;
}

bool Tile::placeOccupant(Character* character){
  if( hasOccupant() ){
    return false;
  }
  _occupant = character;
  _occupant->setTile(this);
  if( _walkEvent ){
    TileEvent e(*_walkEvent);
    e.setCharacter(character);
    raiseEvent(&e);
  }
  return true;
}

void Tile::removeOccupant(){
  _occupant->setTile(NULL);
  _occupant = NULL;
}

Tile* Tile::tileInDirection(Direction dir){
  int x = _x + DirectionDeltaX[dir];
  int y = _y + DirectionDeltaY[dir];
  return (_map->isValidLocation(x,y)) ? _map->tileAt(x,y) : NULL;
}

char Tile::getSymbol() const{
  return _symbol;
}

int Tile::x() const{
  return _x;
}

int Tile::y() const{
  return _y;
}

vector<Item*> Tile::getInventory(){
  return _inventory;
}

void Tile::removeItem(Item* item){
  remove(_inventory.begin(),_inventory.end(),item);
}

void Tile::holdItem(Item* item){
  _inventory.push_back(item);
}

DEF_XML_RESOURCE_LOAD(Tile){
  if( strcmp(node->name(),"tile") != 0 )
    raise(MalformedResourceException,path,string("Expected 'tile' node but found '")+node->name()+"'.");

  //value loading loop
  bool walkable=true;
  string subMapString="";
  string eventString="";
  char symbol='.';
  for(XmlAttribute* attr = node->first_attribute(); attr; attr = attr->next_attribute()){
    if( strcmp(attr->name(),"walkable")==0 ){
      walkable = strcmp(attr->value(),"false")!=0;
    }else if( strcmp(attr->name(),"symbol")==0 ){
      symbol = attr->value()[0];
    }else if( strcmp(attr->name(),"event")==0 ){
      eventString = attr->value();
    }else if( strcmp(attr->name(),"submap")==0 ){
      subMapString = attr->value();
    }
  }

  Map* subMap=NULL;
  TileEvent* event=NULL;
  if( subMapString!="" && manager!=NULL ){
    subMap = manager->loadResource<Map>(Path(subMapString));
  }
  if( eventString!="" ){
    event = new TileEvent(NULL,eventString);
  }

  //the first 3 args will be filled in later, probs not best practice but whatever...
  Tile* tile = new Tile(NULL,0,0, walkable,symbol,event,subMap);

  //fill in the submaps parent
  if(subMap)
    subMap->_parent = tile;

  return tile;
}

