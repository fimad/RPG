#include <cxxtest/TestSuite.h>
#include "map/Map.hpp"
#include "map/Tile.hpp"
#include "map/TileEvent.hpp"
#include "character/Character.hpp"
#include "scripting/EventManager.hpp"
#include "resources/ResourceManager.hpp"
#include "resources/DirectoryProvider.hpp"
#include "scripting/dummy_events.hpp"

//This test assumes that Characters are working correctly

class MapTestSuite : public CxxTest::TestSuite{
  private:
    Map* map;
    Character* c;
    DummyHandler* handler;
    ResourceManager* rman;
  public:
    void setUp(){
      rman = new ResourceManager();
      rman->addProvider(new DirectoryProvider("../../"));

      map = rman->loadResource<Map>(Path("tests/map/test_map.xml"));
      c = rman->loadResource<Character>(Path("tests/character/test_character.xml"));

      handler = new DummyHandler(new TileEvent(NULL,"TRAP"));
      EventManager::global()->subscribe(handler,Path::Any);
    }
    void tearDown(){
      delete map;
      delete c;
      delete handler;
      delete rman;
      EventManager::destroy();
    }

    void test_xml_load(){
      TS_ASSERT_EQUALS(map->width(),2)
      TS_ASSERT_EQUALS(map->height(),2)
    }

    void test_portals(){
      TS_ASSERT(map->tileAt(0,0)->isPortal())
      TS_ASSERT_EQUALS(map->tileAt(0,0)->getSubMap()->width(),1)
    }

    void test_place_character(){
      TS_ASSERT(map->addCharacterAt(0,1,c));
      TS_ASSERT(map->tileAt(0,1)->hasOccupant())
      TS_ASSERT(c->getTile() != NULL)

      map->removeCharacter(c);
      TS_ASSERT(!map->tileAt(0,1)->hasOccupant())
      TS_ASSERT(c->getTile() == NULL)
    }

    void test_walk_event(){
      TS_ASSERT(!handler->didHandle())
      map->addCharacterAt(1,1,c);
      TS_ASSERT(handler->didHandle())
    }

    void test_contents(){
      TS_ASSERT(!map->tileAt(0,1)->hasOccupant())
      map->loadContents();
      TS_ASSERT(map->tileAt(0,1)->hasOccupant())
    }
};

