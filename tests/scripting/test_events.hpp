#include <cxxtest/TestSuite.h>
#include "resources/Path.hpp"
#include "scripting/StringEvent.hpp"
#include "scripting/EventManager.hpp"
#include "scripting/dummy_events.hpp"

class EventsTestSuite : public CxxTest::TestSuite{
  private:
    StringEvent* sevent1;
    StringEvent* sevent2;
    StringEvent* sevent3;
    DummyRaiser* raiser1;
    DummyRaiser* raiser2;
    DummyHandler* handler1;
  public:
    void setUp(){
      EventManager::global();
      sevent1 = new StringEvent("test!");
      sevent2 = new StringEvent("This is a test, yo!");
      sevent3 = new StringEvent("test!");
      raiser1 = new DummyRaiser("dummy/1");
      raiser2 = new DummyRaiser("dummy/2");
      handler1 = new DummyHandler(new StringEvent("test!"));
    }
    void tearDown(){
      EventManager::destroy();
      delete sevent1;
      delete sevent2;
      delete sevent3;
      delete raiser1;
      delete raiser2;
      delete handler1;
    }

    void test_string_event_equal(){
      TS_ASSERT( sevent1->equals(sevent3) );
      TS_ASSERT( !sevent1->equals(sevent2) );
    }

    void test_handle_ignore_wrong_event(){
      EventManager::global()->subscribe(handler1,Path("dummy/1"));
      raiser1->raiseEvent(sevent2);
      TS_ASSERT( !handler1->didHandle() );
    }

    void test_handle_ignore_wrong_raiser(){
      EventManager::global()->subscribe(handler1,Path("dummy/1"));
      raiser2->raiseEvent(sevent1);
      TS_ASSERT( !handler1->didHandle() );
    }

    void test_handle_correct(){
      EventManager::global()->subscribe(handler1,Path("dummy/1"));
      raiser1->raiseEvent(sevent1);
      TS_ASSERT( handler1->didHandle() );
    }

    void test_unsubscribe(){
      EventManager::global()->subscribe(handler1,Path("dummy/1"));
      EventManager::global()->unsubscribe(handler1);
      raiser1->raiseEvent(sevent1);
      TS_ASSERT( !handler1->didHandle() );
    }
};

