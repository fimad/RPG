#include "plot/DialogueList.hpp"
#include "plot/DialogueEvent.hpp"
#include "Errors.hpp"
#include "resources/ResourceDefs.hpp"
#include "rapidxml.hpp"
#include <cstdlib>
#include <cstring>

#include <iostream>
using namespace std;

DialogueNode* xmlNode2DialogueNode(const Path& path, rapidxml::xml_node<>* node, bool isRoot){
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
  if( isRoot && player != "" )
    raise(MalformedResourceException,path,"Root dialogue nodes should not contain player speech!");
  if( !isRoot && player == "" )
    raise(MalformedResourceException,path,"Non-root dialogue nodes MUST contain player speech!");
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
      dnode->addChild( xmlNode2DialogueNode(path,child,false) );
    }
  }

  return dnode;
}

DialogueList* DialogueList::loadFromBuffer(const Path& path, char* c_buffer){
  DialogueList* dialogue = new DialogueList();
  rapidxml::xml_document<> doc;
  try{
    doc.parse<
      rapidxml::parse_trim_whitespace
      | rapidxml::parse_normalize_whitespace
    >(c_buffer);
  }catch(exception& e){
    raise(MalformedResourceException,path,"Malformed xml");
  }
  rapidxml::xml_node<>* node = doc.first_node();

  //make sure this actually looks like a dialogue list xml file
  if( strcmp(node->name(),"dialogue") ){
    raise(MalformedResourceException,path,"Missing 'dialogue' root node");
  }

  //add all the root nodes to the list
  for(node = node->first_node(); node; node = node->next_sibling()){
    dialogue->addBack( xmlNode2DialogueNode(path,node,true) );
  }

  return dialogue;
}

