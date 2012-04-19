#include <cxxtest/TestSuite.h>
#include "scripting/LuaWrapper.hpp"
#include "scripting/Condition.hpp"
#include "scripting/GuardedObject.hpp"
#include "scripting/GuardedList.hpp"

class DummyObject : public GuardedObject{
  public:
    DummyObject(int val, const Condition& cond) : _val(val), GuardedObject(cond) {}
    int value(){ return _val; }
  private:
    int _val;
};

class GuardsTestSuite : public CxxTest::TestSuite{
  private:
    DummyObject* obj1;
    DummyObject* obj2;
    DummyObject* obj3;
    GuardedList<DummyObject>* lst;
  public:
    void setUp(){
      LuaWrapper::setup();
      obj1 = new DummyObject(1, Condition::AlwaysDeny);
      obj2 = new DummyObject(2, Condition::AlwaysAllow);
      obj3 = new DummyObject(3, Condition::AlwaysAllow);
      lst = new GuardedList<DummyObject>();
      lst->addBack(obj1);
      lst->addBack(obj2);
      lst->addBack(obj3);
    }
    void tearDown(){
      LuaWrapper::reset();
      delete obj1;
      delete obj2;
      delete obj3;
      delete lst;
    }

    void test_default_conditions(){
      TS_ASSERT( Condition::AlwaysAllow.allows() );
      TS_ASSERT( !Condition::AlwaysDeny.allows() );
    }

    void test_guarded_object(){
      GuardedObject g1;
      GuardedObject g2(Condition::AlwaysDeny);
      TS_ASSERT( g1.isAllowed() );
      TS_ASSERT( !g2.isAllowed() );
    }

    void test_guarded_list_first(){
      TS_ASSERT_EQUALS( (**lst)->value(), 2 )
    };

    void test_guarded_list_all(){
      TS_ASSERT_EQUALS( lst->getAll().size(), 2 )
    };
};

