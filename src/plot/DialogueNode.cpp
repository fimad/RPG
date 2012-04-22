#include "plot/DialogueNode.hpp"
#include "scripting/GenericEvent.hpp"
#include "plot/DialogueEvent.hpp"
#include <cstring>

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

//DialogueNode* xmlNode2DialogueNode(const Path& path, rapidxml::xml_node<>* node, bool isRoot){
DEF_XML_RESOURCE_LOAD(DialogueNode){
  if( strcmp(node->name(),"node") )
    raise(MalformedResourceException,path,string("Expected 'node', but found '")+node->name()+"'");

  rapidxml::xml_node<>* children = NULL;
  list<string> npc;
  string player = "";
  GenericEvent* event= NULL;
  string condition = "";

  //run over all the nodes to fill in the above values
  for(node = node->first_node(); node; node = node->next_sibling()){
    if( strcmp(node->name(),"npc") == 0 ){
      npc.push_back(node->value());
    }else if( strcmp(node->name(),"player") == 0 ){
      player = node->value();
    }else if( strcmp(node->name(),"condition") == 0 ){
      if( strcmp(node->value(),"") ){ //it looks like cdata doesn't show up in the node's value
        condition = node->value();
      }else if(node->first_node()){ //if the condition is stored in cdata, in the tree it will appear as a node
        condition = node->first_node()->value();
      }else{
        raise(MalformedResourceException,path,"Empty condition!");
      }
    }else if( strcmp(node->name(),"event") == 0 ){
      if( event )
        raise(MalformedResourceException,path,"Multiple event declarations!");
      event = new DialogueEvent(node->value());
    }else if( strcmp(node->name(),"children") == 0 ){
      if( children )
        raise(MalformedResourceException,path,"Multiple children declarations!");
      children = node;
    }else{
      raise(MalformedResourceException,path,string("Unexpected node '")+node->name()+"'");
    }
  }

  //sanity checks
  /* Leave these out for now
  if( isRoot && player != "" )
    raise(MalformedResourceException,path,"Root dialogue nodes should not contain player speech!");
  if( !isRoot && player == "" )
    raise(MalformedResourceException,path,"Non-root dialogue nodes MUST contain player speech!");
    */
  if( npc.size() == 0 )
    raise(MalformedResourceException,path,"NPC speech is required for all dialogue nodes!");

  DialogueNode* dnode = new DialogueNode(npc,player,event);
  if( condition != "" ){
    dnode->setCondition(Condition(condition));
  }

  //load all of the children if they exist
  if( children ){
    for(rapidxml::xml_node<>* child = children->first_node();
        child;
        child = child->next_sibling() ){
      //dnode->addChild( xmlNode2DialogueNode(path,child,false) );
      dnode->addChild( XmlResource::load<DialogueNode>(path,child) );
    }
  }

  return dnode;
}

