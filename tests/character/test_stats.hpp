#include <cxxtest/TestSuite.h>
#include "character/Stats.hpp"
#include "character/Modifier.hpp"
#include "resources/DirectoryProvider.hpp"

class StatsTestSuite : public CxxTest::TestSuite{
  private:
    Stats* stats;
    Modifier* str_mod;
  public:
    void setUp(){
      stats = new Stats();
      stats->setBaseStat(Stats::STR, 8);
      stats->setBaseStat(Stats::DEX, 9);
      stats->setBaseStat(Stats::CON, 10);
      stats->setBaseStat(Stats::INT, 12);
      stats->setBaseStat(Stats::WIS, 13);
      stats->setBaseStat(Stats::CHA, 14);

      str_mod = new Modifier("strength mod");
      str_mod->setValueFor(Stats::STR_MOD, 1);
    }
    void tearDown(){
      delete stats;
      delete str_mod;
    }

    void test_stats_abilities(){
      TS_ASSERT_EQUALS(stats->getStat(Stats::STR), 8);
    }

    void test_stats_ability_modifiers(){
      TS_ASSERT_EQUALS(stats->getStat(Stats::STR_MOD), -1);
      TS_ASSERT_EQUALS(stats->getStat(Stats::DEX_MOD), -1);
      TS_ASSERT_EQUALS(stats->getStat(Stats::CON_MOD), 0);
      TS_ASSERT_EQUALS(stats->getStat(Stats::INT_MOD), 1);
      TS_ASSERT_EQUALS(stats->getStat(Stats::WIS_MOD), 1);
      TS_ASSERT_EQUALS(stats->getStat(Stats::CHA_MOD), 2);
    }

    void test_stats_modifiers(){
      stats->addModifier(str_mod);
      TS_ASSERT_EQUALS(stats->getStat(Stats::STR_MOD), 0);
      stats->removeModifier(str_mod);
      TS_ASSERT_EQUALS(stats->getStat(Stats::STR_MOD), -1);
    }

    void test_string_to_stat(){
      Stats::Stat stat;
      TS_ASSERT( Stats::getStatForString("dex",&stat) );
      TS_ASSERT_EQUALS( stat, Stats::DEX );
    }

    void test_xml_load(){
      //load the xml file
      string xmlPath = "../../tests/character/test_stats.xml";
      char* xml = DirectoryProvider::readFile(xmlPath);
      Stats* s = XmlResource::load<Stats>(Path("test_stats.xml"),xml);
      free(xml);

      //test it
      TS_ASSERT_EQUALS(s->getStat(Stats::STR), 8);
      TS_ASSERT_EQUALS(s->getStat(Stats::CHA), 14);
      TS_ASSERT_EQUALS(s->getStat(Stats::DEX), 9);
    }

};

