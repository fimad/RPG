#include "plot/DialogueNode.hpp"
#include "scripting/GenericEvent.hpp"

DialogueNode::DialogueNode(const string& npc, const string& player, GenericEvent* event)
  : _playerSays(player)
  , _event(event)
{
  _npcResponse.push_front(npc);
}

DialogueNode::DialogueNode(const list<string>& npc, const string& player, GenericEvent* event)
  : _npcResponse(npc)
  , _playerSays(player)
  , _event(event)
{}

DialogueNode::~DialogueNode(){
  if( _event )
    delete _event;
}

const string& DialogueNode::playerSays() const{
  return _playerSays;
}

const list<string>& DialogueNode::npcResponse() const{
  return _npcResponse;
}

void DialogueNode::addChild(DialogueNode* child){
  _children.addBack(child);
}

list<DialogueNode*> DialogueNode::options() const{
  return _children.getAll();
}

bool DialogueNode::hasEvent() const{
  return _event != NULL;
}

GenericEvent* DialogueNode::getEvent() const{
  return _event;
}

