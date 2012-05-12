#include <cxxtest/TestSuite.h>
#include "resources/ResourceManager.hpp"
#include "resources/DirectoryProvider.hpp"
#include "character/Item.hpp"

class ItemTestSuite : public CxxTest::TestSuite{
  private:
  public:
    void setUp(){}
    void tearDown(){}

    void test_xml_load(){
      ResourceManager* rman = new ResourceManager();
      rman->addProvider(new DirectoryProvider("../../"));

      //load the xml file
      string xmlPath = "tests/character/test_item.xml";
      Item *i = rman->loadResource<Item>(Path(xmlPath));

      //tests
      TS_ASSERT_EQUALS(i->getName(), "Test Item")
      TS_ASSERT_EQUALS(i->getDescription(), "Test Description")
      TS_ASSERT_EQUALS(i->getSellPrice(), 100)
      TS_ASSERT_EQUALS(i->getBuyPrice(), 50)
      TS_ASSERT_EQUALS(i->getDamage()->str(), "100d6")
    }

};

