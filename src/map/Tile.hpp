#ifndef _TILE_HPP_
#define _TILE_HPP_

#include "resources/XmlResource.hpp"
#include "scripting/GuardedList.hpp"
#include "scripting/EventRaiser.hpp"
#include "map/Direction.hpp"

class Map;
class Character;
class TileEvent;

class Tile : public XmlResource {
  public:
    Tile(Map* map, int x, int y, bool walkable, char symbol='.', TileEvent* walkEvent=NULL, Map* subMap=NULL);
    ~Tile();
    bool isPortal() const; //has a submap associated with it
    bool isWalkable() const;
    bool hasOccupant() const;
    Character* getOccupant() const;
    Map* getSubMap() const;
    Map* getMap() const;
    char getSymbol() const;
    int x() const;
    int y() const;
    bool placeOccupant(Character* character); //false on failure
    void removeOccupant();
    Tile* tileInDirection(Direction dir); //NULL on failure

    friend class XmlResource;
  private:
    char _symbol;
    Map* _map;
    int _x,_y;
    bool _walkable;
    Character* _occupant;
    TileEvent* _walkEvent;
    Map* _subMap;
};
MAKE_XML_RESOURCE(Tile)

#endif

