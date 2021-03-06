#include <cxxtest/TestSuite.h>
#include "character/Race.hpp"
#include "character/Modifier.hpp"
#include "character/CharacterClass.hpp"
#include "resources/DirectoryProvider.hpp"

class RaceClassTestSuite : public CxxTest::TestSuite{
  private:
    Race* race;
    CharacterClass* charClass;
  public:
    void setUp(){
      //Setup some modifiers for the character class
      list<Modifier*> classMods{
          new Modifier("m1")
        , new Modifier("m2")
        , new Modifier("m3")
      };
      classMods.front()->setValueFor(Stats::STR_MOD,1);
      auto a = classMods.begin();
      a++;
      (*a)->setValueFor(Stats::STR_MOD,2);
      classMods.back()->setValueFor(Stats::STR_MOD,3);
      charClass = new CharacterClass("test class", "A class made up for testing.", classMods);
      
      race = new Race("test race","A race made up for testing.",new Modifier("race mod"));
      race->getModifier()->setValueFor(Stats::STR_MOD,1);
    }
    void tearDown(){
      delete race;
      delete charClass;
    }

    void test_race_create(){
      TS_ASSERT_EQUALS(race->getName(), "test race");
      TS_ASSERT_EQUALS(race->getModifier()->valueFor(Stats::STR_MOD), 1 );
    }

    void test_character_class_create(){
      TS_ASSERT_EQUALS(charClass->getName(), "test class");
      TS_ASSERT_EQUALS(charClass->getModifier()->valueFor(Stats::STR_MOD), 1);
      TS_ASSERT_EQUALS(charClass->maxLevel(), 3);
      TS_ASSERT_EQUALS(charClass->currentLevel(), 1);
    }
    
    void test_character_class_levels(){
      TS_ASSERT_EQUALS(charClass->canLevelUp(), true);

      charClass->levelUp();
      TS_ASSERT_EQUALS(charClass->canLevelUp(), true);
      TS_ASSERT_EQUALS(charClass->currentLevel(), 2);
      TS_ASSERT_EQUALS(charClass->getModifier()->valueFor(Stats::STR_MOD), 2);

      charClass->setLevel(3);
      TS_ASSERT_EQUALS(charClass->canLevelUp(), false);
      TS_ASSERT_EQUALS(charClass->currentLevel(), 3);
      TS_ASSERT_EQUALS(charClass->getModifier()->valueFor(Stats::STR_MOD), 3);
    }

    void test_race_xml_load(){
      string xmlPath = "../../tests/character/test_race.xml";
      char* xml = DirectoryProvider::readFile(xmlPath);
      Race* r = XmlResource::load<Race>(Path("test_race.xml"),xml);
      free(xml);

      TS_ASSERT_EQUALS( r->getName(), "Test Race" );
      TS_ASSERT_EQUALS( r->getDescription(), "This is a description of the test race." );
      TS_ASSERT_EQUALS( r->getModifier()->valueFor(Stats::STR), 2 );
      TS_ASSERT_EQUALS( r->getModifier()->valueFor(Stats::CHA), -2 );
    }

    void test_class_xml_load(){
      string xmlPath = "../../tests/character/test_class.xml";
      char* xml = DirectoryProvider::readFile(xmlPath);
      CharacterClass* c = XmlResource::load<CharacterClass>(Path("test_class.xml"),xml);
      free(xml);

      TS_ASSERT_EQUALS( c->getName(), "Test Class" );
      TS_ASSERT_EQUALS( c->getDescription(), "This is a description of the test class." );
      TS_ASSERT_EQUALS( c->getModifier()->valueFor(Stats::ATTACK_BONUS), 1 );
      TS_ASSERT_EQUALS( c->maxLevel(), 3 );

      c->levelUp();
      TS_ASSERT_EQUALS( c->getModifier()->valueFor(Stats::ATTACK_BONUS), 2 );
      c->levelUp();
      TS_ASSERT_EQUALS( c->getModifier()->valueFor(Stats::ATTACK_BONUS), 3 );
      c->levelUp();
      TS_ASSERT_EQUALS( c->getModifier()->valueFor(Stats::ATTACK_BONUS), 3 );
    }
};

