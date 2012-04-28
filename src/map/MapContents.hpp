#ifndef _MAP_CONTENTS_HPP_
#define _MAP_CONTENTS_HPP_

#include "resources/XmlResource.hpp"
#include <set>
#include <tuple>
using namespace std;

//TODO:items
//TODO:player as well as character, also character should probably get changed to npc once that gets figured out

class Map;
class Character;

//transfers ownership of objects to the Map it gives them to
class MapContents : public XmlResource{
  public:
    MapContents(set<tuple<int,int,Character*>> characters);
    void fill(Map* map);
  private:
    set<tuple<int,int,Character*>> _characters;
    //set<tuple<int,int,Item*>> _items;
};
MAKE_XML_RESOURCE(MapContents)

#endif

