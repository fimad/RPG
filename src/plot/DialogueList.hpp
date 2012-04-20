#ifndef _DIALOGUE_HPP_
#define _DIALOGUE_HPP_

#include "scripting/GuardedList.hpp"
#include "resources/Resource.hpp"
#include "plot/DialogueNode.hpp"

class DialogueList : public GuardedList<DialogueNode>, public Resource{
  public:
    static DialogueList* loadFromBuffer(const Path& path, const string& buffer);
};

#endif

