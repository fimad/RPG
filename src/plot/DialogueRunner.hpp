#ifndef _DIALOGUE_RUNNER_HPP_
#define _DIALOGUE_RUNNER_HPP_

#include <list>
#include <string>
#include <vector>
using namespace std;

class DialogueList;
class DialogueNode;
class EventRaiser;
class DialogueRunner{
  public:
    DialogueRunner(EventRaiser* raiser, DialogueList* dlist);
    const list<string> npcSpeech() const;
    int numOptions() const;
    const string& getOption(int i) const;
    void chooseOption(int i);
    bool isFinished() const;
  private:
    void updateCurrent(DialogueNode* newCurrent);
    vector<DialogueNode*> _currentOptions;
    DialogueNode* _root;
    DialogueNode* _current;
    EventRaiser* _raiser;
    bool _isFinished;
};

#endif

