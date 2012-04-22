#ifndef _DIALOGUE_HPP_
#define _DIALOGUE_HPP_

#include "scripting/GuardedList.hpp"
#include "resources/XmlResource.hpp"
#include "plot/DialogueNode.hpp"

class DialogueList : public XmlResource, public GuardedList<DialogueNode> {
  public:
    static DialogueList* loadFromBuffer(const Path& path, char* buffer);
};
MAKE_XML_RESOURCE(DialogueList)

#endif

