#include <cxxtest/TestSuite.h>
#include "character/Race.hpp"
#include "character/Stats.hpp"
#include "character/Modifier.hpp"
#include "character/Character.hpp"
#include "character/CharacterClass.hpp"
#include "resources/ResourceManager.hpp"
#include "resources/DirectoryProvider.hpp"

class CharacterTestSuite : public CxxTest::TestSuite{
  private:
    Race* race;
    CharacterClass* charClass;
    Stats* stats;
    Character* character;
  public:
    void setUp(){
      list<Modifier*> classMods{
          new Modifier("m1")
      };
      classMods.front()->setValueFor(Stats::STR_MOD,1);
      charClass = new CharacterClass("test class", "A class made up for testing.", classMods);

      race = new Race("test race","A race made up for testing.",new Modifier("race mod"));
      race->getModifier()->setValueFor(Stats::STR_MOD,1);

      stats = new Stats();
      stats->setBaseStat(Stats::STR, 8);

      character = new Character("Test Char", race, charClass, stats);
    }
    void tearDown(){
      delete character;
    }

    void test_race_class(){
      TS_ASSERT_EQUALS(character->getStats()->getStat(Stats::STR_MOD), 1);
    }

    void test_xml_load(){
      ResourceManager* rman = new ResourceManager();
      rman->addProvider(new DirectoryProvider("../../"));

      //load the xml file
      string xmlPath = "tests/character/test_character.xml";
      Character*c = rman->loadResource<Character>(Path(xmlPath));

      //test it
      TS_ASSERT_EQUALS(c->getName(), "My Name");
      TS_ASSERT_EQUALS(c->getRace()->getName(), "Test Race");
      TS_ASSERT_EQUALS(c->getClasses().front()->getName(), "Test Class");
      TS_ASSERT_EQUALS(c->getClasses().front()->currentLevel(), 2);
      TS_ASSERT_EQUALS(c->getHP(), 10);
      TS_ASSERT_EQUALS(c->getMP(), 11);
      TS_ASSERT_EQUALS(c->getExp(), 12);
      TS_ASSERT_EQUALS(c->getStats()->getStat(Stats::STR), 10);

      delete rman;
    }
};

