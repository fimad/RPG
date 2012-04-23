#include <cxxtest/TestSuite.h>
#include "character/Modifier.hpp"
#include "character/ProxyModifier.hpp"

class ModifiersTestSuite : public CxxTest::TestSuite{
  private:
    Modifier* m1;
    Modifier* m2;
    Modifier* m3;
    ProxyModifier* pm;
  public:
    void setUp(){
      m1 = new Modifier("m1");
      m2 = new Modifier("m2");
      m3 = new Modifier("m3");
      pm = new ProxyModifier("pm", m1);

      m1->setValueFor(Stats::STR_MOD,1);
      m1->setValueFor(Stats::WIS_MOD,1);
      m2->setValueFor(Stats::CON_MOD,1);
      m3->setValueFor(Stats::DEX_MOD,1);
    }
    void tearDown(){
      delete m1;
      delete m2;
      delete m3;
      delete pm;
    }

    void test_modifier_values(){
      TS_ASSERT_EQUALS(m1->valueFor(Stats::STR_MOD), 1)
      TS_ASSERT_EQUALS(m1->valueFor(Stats::WIS_MOD), 1)
      TS_ASSERT_EQUALS(m1->valueFor(Stats::CON_MOD), 0)
    }

    void test_proxy_modifier(){
      TS_ASSERT_EQUALS(pm->valueFor(Stats::STR_MOD), 1)
      TS_ASSERT_EQUALS(pm->valueFor(Stats::WIS_MOD), 1)
      TS_ASSERT_EQUALS(pm->valueFor(Stats::CON_MOD), 0)
    }

    void test_proxy_modifier_switch(){
      pm->setModifier(m2);
      TS_ASSERT_EQUALS(pm->valueFor(Stats::STR_MOD), 0)
      TS_ASSERT_EQUALS(pm->valueFor(Stats::CON_MOD), 1)
    }
};

