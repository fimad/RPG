#include <cxxtest/TestSuite.h>
#include "character/Race.hpp"
#include "character/Stats.hpp"
#include "character/Modifier.hpp"
#include "character/Character.hpp"
#include "character/CharacterClass.hpp"

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

};

