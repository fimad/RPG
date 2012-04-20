#include <cxxtest/TestSuite.h>
#include "plot/DialogueEvent.hpp"
#include "plot/DialogueList.hpp"
#include "plot/DialogueNode.hpp"
#include "plot/DialogueRunner.hpp"
#include "scripting/EventManager.hpp"
#include "scripting/LuaWrapper.hpp"
#include "scripting/dummy_events.hpp"
#include <cstring>

string dialogue_xml = " \
<dialogue> \
  <node> \
    <npc> \
    Howdy! \
    </npc> \
    <children> \
      <node> \
          <player> \
            Fuck You! \
          </player> \
          <npc> \
            That's not nice :( \
          </npc> \
          <npc> \
            I'm leaving \
          </npc> \
          <event> \
            Insulted NPC\
          </event> \
      </node> \
      <node> \
        <player> \
          Well hey there! \
        </player> \
        <npc> \
          What brings you here?? \
        </npc> \
        <children> \
          <node> \
            <player> \
              I must leave! \
            </player> \
            <npc> \
              OK! \
            </npc> \
          </node> \
        </children> \
      </node> \
      <node> \
        <condition><![CDATA[ \
          false \
        ]]></condition> \
        <player> \
          I should not even be an option! \
        </player> \
        <npc> \
          I AM THE QUEEN OF FRANCE! \
        </npc> \
      </node> \
    </children> \
  </node> \
</dialogue> \
";

class DialogueTestSuite : public CxxTest::TestSuite{
  private:
    DialogueList* dl;
    DialogueRunner* runner;
    DummyHandler* handler;
    DummyRaiser* raiser;
    char* tmp;
  public:
    void setUp(){
      LuaWrapper::setup();
      raiser = new DummyRaiser("dummy/1");
      handler = new DummyHandler(new DialogueEvent("Insulted NPC"));
      EventManager::global()->subscribe(handler,raiser->getPath());

      tmp = (char*)malloc(dialogue_xml.size()+1);
      memcpy(tmp,dialogue_xml.c_str(),dialogue_xml.size());
      tmp[dialogue_xml.size()] = 0;

      dl = DialogueList::loadFromBuffer(Path("from memory"),tmp);
      free(tmp);

      runner = new DialogueRunner(raiser,dl);
    }
    void tearDown(){
      LuaWrapper::reset();
      EventManager::destroy();
      delete dl;
      delete runner;
      delete raiser;
      delete handler;
    }

    void test_load_from_buffer(){
      TS_ASSERT_EQUALS(dl->size(),1)
      TS_ASSERT_EQUALS((**dl)->options().size(),2)
      TS_ASSERT_EQUALS((**dl)->options().front()->playerSays(), "Fuck You!")
      TS_ASSERT_EQUALS((**dl)->options().front()->npcResponse().front(), "That's not nice :(")
      TS_ASSERT_EQUALS((**dl)->options().front()->npcResponse().back(), "I'm leaving")
    }

    void test_dialogue_runner(){
      TS_ASSERT_EQUALS(runner->npcSpeech().front(),"Howdy!")
      TS_ASSERT_EQUALS(runner->numOptions(),2)
      TS_ASSERT_EQUALS(runner->getOption(0),"Fuck You!")
      TS_ASSERT_EQUALS(runner->getOption(1),"Well hey there!")
      runner->chooseOption(1);
      TS_ASSERT_EQUALS(runner->npcSpeech().front(),"What brings you here??")
      runner->chooseOption(0);
      TS_ASSERT(runner->isFinished())
    }

    void test_dialogue_runner_events(){
      runner->chooseOption(0);
      TS_ASSERT(handler->didHandle())
    }
};

