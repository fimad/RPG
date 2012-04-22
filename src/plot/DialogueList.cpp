#include "plot/DialogueList.hpp"
#include "plot/DialogueEvent.hpp"
#include "Errors.hpp"
#include "resources/ResourceDefs.hpp"
#include "rapidxml.hpp"
#include <cstdlib>
#include <cstring>

#include <iostream>
using namespace std;

DEF_XML_RESOURCE_LOAD(DialogueList){
  DialogueList* dialogue = new DialogueList();

  //make sure this actually looks like a dialogue list xml file
  if( strcmp(node->name(),"dialogue") ){
    raise(MalformedResourceException,path,"Missing 'dialogue' root node");
  }

  //add all the root nodes to the list
  for(node = node->first_node(); node; node = node->next_sibling()){
    //dialogue->addBack( xmlNode2DialogueNode(path,node,true) );
    dialogue->addBack( XmlResource::load<DialogueNode>(path,node) );
  }

  return dialogue;
}

