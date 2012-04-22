#ifndef _DIALOGUE_HPP_
#define _DIALOGUE_HPP_

#include "scripting/GuardedList.hpp"
#include "resources/XmlResource.hpp"
#include "plot/DialogueNode.hpp"

//class DialogueList : public GuardedList<DialogueNode>, public Resource{
//BEGIN_XML_RESOURCE(DialogueList), public GuardedList<DialogueNode> {
BEGIN_XML_RESOURCE_INHERITS(DialogueList, public GuardedList<DialogueNode>)
  public:
    static DialogueList* loadFromBuffer(const Path& path, char* buffer);
//};
END_XML_RESOURCE(DialogueList)

#endif

