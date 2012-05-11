#include "game/Die.hpp"
#include <cxxtest/TestSuite.h>

class ItemTestSuite : public CxxTest::TestSuite{
  private:
  public:
    void setUp(){}
    void tearDown(){
      Die::clear();
    }

    void test_2d6(){
      Die* d1 = Die::parse("2d6");
      for(int i=0; i<100; i++){
        int v = d1->roll();
        TS_ASSERT_LESS_THAN_EQUALS(v,12)
        TS_ASSERT_LESS_THAN_EQUALS(2,v)
      }
    }

    void test_complex(){
      Die* d1 = Die::parse("2d6-3d4");
      for(int i=0; i<100; i++){
        int v = d1->roll();
        TS_ASSERT_LESS_THAN_EQUALS(v,9)
        TS_ASSERT_LESS_THAN_EQUALS(-10,v)
      }
    }

    void test_sign(){
      Die* d1 = Die::parse("-d6");
      for(int i=0; i<100; i++){
        int v = d1->roll();
        TS_ASSERT_LESS_THAN_EQUALS(v,-1)
        TS_ASSERT_LESS_THAN_EQUALS(-6,v)
      }
    }

    void test_singleton(){
      TS_ASSERT( Die::parse("d6") == Die::parse("d6") )
    }
};

