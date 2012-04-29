#ifndef _MAP_HPP_
#define _MAP_HPP_

#include "resources/XmlResource.hpp"
#include "scripting/GuardedObject.hpp"
#include <set>
using namespace std;

//TODO:maps should also track items

class Tile;
class Character;

class Map : public XmlResource, public GuardedObject{
  public:
    Map(int width, int height, Tile* parent=NULL);
    ~Map();
    int width() const;
    int height() const;
    bool hasParent() const;
    Tile* parent() const;
    Tile* tileAt(int x, int y) const;
    void setTileAt(int x, int y, Tile* tile);
    bool isValidLocation(int x, int y) const;
    void removeCharacter(Character* c);
    bool addCharacterAt(int x, int y, Character* c);
    void setContentsPath(const Path& path);
    void loadContents();
    void step(double delta);

    friend class XmlResource;
  private:
    int _width;
    int _height;
    Tile** _tiles;
    Tile* _parent;
    bool _haveContents; //has _contents been set?
    Path _contents; //TODO: initial configurations for maps
    set<Character*> _npcs;
};
MAKE_XML_RESOURCE(Map)

#endif

