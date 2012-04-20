#include "plot/DialogueRunner.hpp"
#include "plot/DialogueList.hpp"
#include "plot/DialogueNode.hpp"
#include "scripting/EventRaiser.hpp"

DialogueRunner::DialogueRunner(EventRaiser* raiser, DialogueList* dlist){
  _root = dlist->getFirst();
  _raiser = raiser;
  updateCurrent(_root);
}

const list<string> DialogueRunner::npcSpeech() const{
  return _current->npcResponse();
}

int DialogueRunner::numOptions() const{
  return _currentOptions.size();
}

const string& DialogueRunner::getOption(int i) const{
  return _currentOptions[i]->playerSays();
}

void DialogueRunner::chooseOption(int i){
  updateCurrent(_currentOptions[i]);
}

bool DialogueRunner::isFinished() const{
  return _isFinished;
}

void DialogueRunner::updateCurrent(DialogueNode* newCurrent){
  _current = newCurrent;
  list<DialogueNode*> optionList = _current->options();
  _currentOptions = vector<DialogueNode*>(optionList.begin(), optionList.end());
  _isFinished = !_currentOptions.size();
  if( _current->hasEvent() ){
    _raiser->raiseEvent(_current->getEvent());
  }
}

