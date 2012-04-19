#include <cxxtest/TestSuite.h>
#include "dummy_events.hpp"
#include "scripting/LuaWrapper.hpp"
#include "SLB/SLB.hpp"
#include "scripting/EventManager.hpp"
#include "scripting/StringEvent.hpp"
#include <iostream>
using namespace std;

class LuaTestSuite : public CxxTest::TestSuite{
  private:
    DummyRaiser* raiser;
    DummyHandler* handler;
    StringEvent* testEvent;
    static bool isSet;
  public:
    static void setMe(){
      isSet = true;
    }

    void setUp(){
      isSet = false;
      LuaWrapper::setup();

      testEvent = new StringEvent("test");
      raiser = new DummyRaiser("dummy/1");
      handler = new DummyHandler(new StringEvent("test"));
      EventManager::global()->subscribe(handler,raiser->getPath());

      //attempt to export some values
      SLB::Manager::defaultManager()->set("setMe",SLB::FuncCall::create(&setMe));
      SLB::Manager::defaultManager()->set("raiser",new SLB::RefValue<EventRaiser>(raiser));
      SLB::Manager::defaultManager()->set("testEvent",new SLB::RefValue<StringEvent>(testEvent));

      LuaWrapper::doString("setMe = SLB.setMe");
      LuaWrapper::doString("raiser = SLB.raiser");
      LuaWrapper::doString("testEvent = SLB.testEvent");
    }

    void tearDown(){
      LuaWrapper::reset();
      EventManager::destroy();
      delete raiser;
      delete handler;
      delete testEvent;
    }

    void test_setme(){
      LuaWrapper::doString("setMe()");
      TS_ASSERT(isSet);
    }

    void test_create_path(){
      LuaWrapper::doString(" \
        p1 = Path(\"test\") \
        if( p1:toString() == \"test\" ) then \
          setMe() \
        end \
        setMe()\
      ");
      TS_ASSERT(isSet);
    }

    void test_create_string_event(){
      LuaWrapper::doString(" \
        s1 = StringEvent(\"test\") \
        if( s1:value() == \"test\" ) then \
          setMe() \
        end \
      ");
      TS_ASSERT(isSet);
    }

    void test_export_value(){
      LuaWrapper::doString(" \
        if( testEvent:value() == \"test\" ) then \
          setMe() \
        end \
      ");
      TS_ASSERT(isSet);
    }

    void test_export_raiser(){
      LuaWrapper::doString("\
        if( raiser:getPath():toString() == \"dummy/1\" ) then \
          setMe() \
        end \
      ");
      TS_ASSERT(isSet);
    }

    void test_raise_event(){
      LuaWrapper::doString("raiser:raiseEvent(testEvent)");
      TS_ASSERT(handler->didHandle());
    }

    void test_evaluate(){
      TS_ASSERT(LuaWrapper::evaluate<bool>("'a' == 'a'"));
      TS_ASSERT(!LuaWrapper::evaluate<bool>("'a' == 'b'"));
    }
};

bool LuaTestSuite::isSet = false;

