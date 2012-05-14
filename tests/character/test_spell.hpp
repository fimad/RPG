#include <cxxtest/TestSuite.h>
#include "scripting/LuaWrapper.hpp"
#include "resources/ResourceManager.hpp"
#include "resources/DirectoryProvider.hpp"
#include "character/Spell.hpp"

class SpellTestSuite : public CxxTest::TestSuite{
  private:
  public:
    void setUp(){
      LuaWrapper::setup();
    }
    void tearDown(){
      LuaWrapper::reset();
    }

    void test_xml_load(){
      ResourceManager* rman = new ResourceManager();
      rman->addProvider(new DirectoryProvider("../../"));

      //load the xml file
      string xmlPath = "tests/character/test_spell.xml";
      Spell *s = rman->loadResource<Spell>(Path(xmlPath));

      //tests
      TS_ASSERT_EQUALS(s->getName(), "Print Hello")
      TS_ASSERT_EQUALS(s->getDescription(), "Prints \"Hello\" to stdout")
      TS_ASSERT_EQUALS(s->cast(NULL,NULL), 47)
    }

};

