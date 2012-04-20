#ifndef _DIALOGUE_NODE_HPP_
#define _DIALOGUE_NODE_HPP_

#include "scripting/GuardedObject.hpp"
#include "scripting/GuardedList.hpp"
#include <string>
using namespace std;

class GenericEvent;
class DialogueNode : public GuardedObject {
  public:
    //the DialogueNode will own the event
    DialogueNode(const string& npc, const string& player = "", GenericEvent* event = NULL);
    DialogueNode(const list<string>& npc, const string& player = "", GenericEvent* event = NULL);
    ~DialogueNode();
    const string& playerSays() const;
    const list<string>& npcResponse() const;
    void addChild(DialogueNode* child);
    list<DialogueNode*> options() const;
    bool hasEvent() const;
    GenericEvent* getEvent() const;

  private:
    string _playerSays;
    list<string> _npcResponse;
    GuardedList<DialogueNode> _children;
    GenericEvent* _event;
};

#endif

