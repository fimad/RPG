#include "map/Map.hpp"
#include "map/Tile.hpp"
#include "map/MapContents.hpp"
#include "character/Character.hpp"
#include "resources/ResourceManager.hpp"
#include <cstdlib>
#include <cstring>

Map::Map(int width, int height, Tile* parent)
  : _width(width)
  , _height(height)
  , _parent(parent)
  , _contents(Path::Any)
{
  _tiles = (Tile**)calloc(width*height,sizeof(Tile*));
  _haveContents = false;
}

Map::~Map(){
  //delete all the tiles
  for(int y=0; y<_height; y++){
    for(int x=0; x<_width; x++){
      Tile* t = tileAt(x,y);
      if( t!=NULL ){
        delete t;
      }
    }
  }
  free(_tiles);
}

int Map::width() const{
  return _width;
}

int Map::height() const{
  return _height;
}

bool Map::hasParent() const{
  return _parent != NULL;
}

Tile* Map::parent() const{
  return _parent;
}

void Map::setTileAt(int x, int y, Tile* tile){
  Tile** t = (_tiles+x+y*_width);
  *t = tile;
}

Tile* Map::tileAt(int x, int y) const{
  return _tiles[x+y*_width];
}

bool Map::isValidLocation(int x, int y) const{
  return (x>=0 && y>=0 && x<_width && y<_height);
}

void Map::removeCharacter(Character* c){
  c->getTile()->removeOccupant();
  _npcs.erase(c);
}

bool Map::addCharacterAt(int x, int y, Character* c){
  if(isValidLocation(x,y) && tileAt(x,y)->placeOccupant(c)){
    _npcs.insert(c);
    return true;
  }
  return false;
}

void Map::setContentsPath(const Path& path){
  _haveContents = true;
  _contents = path;
}

void Map::loadContents(){
  if( _haveContents ){
    MapContents* mc = getManager()->loadResource<MapContents>(_contents);
    mc->fill(this);
    delete mc;
  }

  //load all of the sub maps contents if they have them as well
  for(int y=0; y<_height; y++){
    for(int x=0; x<_width; x++){
      Tile* t = tileAt(x,y);
      if( t->isPortal() ){
        t->getSubMap()->loadContents();
      }
    }
  }
}

DEF_XML_RESOURCE_LOAD(Map){
  if( strcmp(node->name(),"map") != 0 )
    raise(MalformedResourceException,path,string("Expected 'map' node but found '")+node->name()+"'.");

  //value loading loop
  int width=0;
  int height=0;
  string contents="";
  XmlNode* tiles=NULL;
  for(XmlAttribute* attr = node->first_attribute(); attr; attr = attr->next_attribute()){
    if( strcmp(attr->name(),"width")==0 ){
      width = atoi(attr->value());
    }else if( strcmp(attr->name(),"height")==0 ){
      height = atoi(attr->value());
    }else if( strcmp(attr->name(),"contents")==0 ){
      contents = attr->value();
    }
  }
  for(XmlNode* child = node->first_node(); child; child = child->next_sibling()){
    if( strcmp(child->name(),"tiles")==0 ){
      tiles = child;
    }
  }

  //sanity checks
  if( width<=0 )
    raise(MalformedResourceException,path,"Invalid width for map.");
  if( height<=0 )
    raise(MalformedResourceException,path,"Invalid height for map.");
  if( tiles==NULL )
    raise(MalformedResourceException,path,"'tiles' node required for map.");

  Map* map = new Map(width,height);
  if( contents!="" ){
    map->setContentsPath(Path(contents));
  }

  //load each tile
  int x,y;
  XmlNode* tile = tiles->first_node();
  for(y=0; y<height && tile; y++){
    for(x=0; x<width && tile; x++){
      try{
        Tile* t = XmlResource::load<Tile>(path,tile,manager);
        t->_x = x;
        t->_y = y;
        t->_map = map;
        map->setTileAt(x,y, t);
      }catch(MalformedResourceException& e){
        delete map;
        throw e;
      }
      tile = tile->next_sibling();
    }
  }
  if( x!=width || y!= height ){
    delete map;
    raise(MalformedResourceException,path,"Not enough tiles");
  }

  return map;
}

