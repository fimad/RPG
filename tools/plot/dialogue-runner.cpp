#include "resources/DirectoryProvider.hpp"
#include "resources/ResourceManager.hpp"
#include "scripting/dummy_events.hpp"
#include "scripting/EventManager.hpp"
#include "scripting/StringEvent.hpp"
#include "scripting/LuaWrapper.hpp"
#include "plot/DialogueRunner.hpp"
#include "plot/DialogueEvent.hpp"
#include "plot/DialogueList.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class EchoHandler : public EventHandler{
  void handleEvent(Path raiser, GenericEvent* event){
    StringEvent* sevent;
    DialogueEvent* devent;

    cout << "EVENT: ";
    if( (sevent=dynamic_cast<StringEvent*>(event)) ){
      cout << "String Event ('" << sevent->value() << "')";
    }else if( (devent=dynamic_cast<DialogueEvent*>(event)) ){
      cout << "Dialogue Event ('" << devent->value() << "')";
    }else{
      cout << "Unknown type." << endl;
    }
    cout << endl;
  }
};

char* readFile(const char* filename){
  ifstream file(filename);
  if(!file){
    cerr << "Could not open '" << filename << "'!" << endl;
    exit(-1);
  }

  //read the file in chunks at a time
  char read_buffer[1024];
  string buffer = "";
  while( !file.eof() ){
    int numRead = file.readsome(read_buffer,1024-1);
    if( numRead == 0 )
      break;
    read_buffer[numRead] = 0;
    buffer += read_buffer;
  }

  //copy it into a modifiable c string
  char* c_buffer = (char*)malloc(buffer.size()+1);
  memcpy(c_buffer,buffer.c_str(),buffer.size());
  c_buffer[buffer.size()] = 0;

  return c_buffer;
}

int getInt(int max){
  int chosen = -1;
  string tmp;
  while(chosen == -1){
    cout << "[0-" << max << "]? ";
    cin >> chosen;
    if( chosen > max || chosen < 0)
      chosen = -1;
  }
  return chosen;
}

void npcSpeak(list<string> lines){
  for( string line : lines ){
    cout << "NPC: " << line << endl;
  }
}

int main(int argc, char* argv[]){
  if( argc != 2 ){
    cerr << "Usage: " << argv[0] << " dialogue.xml" << endl;
    return 1;
  }

  //we must initialize lua because DialogueNodes are Guarded and use Condition's
  LuaWrapper::setup();

  //We need a raiser, and make a handler that will echo when events happen
  DummyRaiser* raiser = new DummyRaiser("dummy/1");
  EchoHandler* handler = new EchoHandler();
  EventManager::global()->subscribe(handler,raiser->getPath());

  //load the dialogue
  char* buffer = readFile(argv[1]);
  DialogueList* dialogueList = DialogueList::loadFromBuffer(Path("file"),buffer);
  free(buffer);

  //Choose which root node to play
  list<DialogueNode*> rootsList = dialogueList->getAll();
  vector<DialogueNode*> rootsVector(rootsList.begin(),rootsList.end());
  DialogueNode* chosenRoot = NULL;
  if( rootsVector.size() == 0 ){
    cerr << "There are no root dialogue nodes!" << endl;
    return -1;
  }else if(rootsVector.size() == 1){
    chosenRoot = rootsVector[0];
  }else{
    cout << "Choose a root node, npc says:" << endl;
    for( int i=0; i<rootsVector.size(); i++ ){
      cout << "\t" << i << ".) " << rootsVector[i]->npcResponse().front() << endl;
    }
    chosenRoot = rootsVector[getInt(rootsVector.size()-1)];
  }

  //Create a dialogue runner for the chosen root
  DialogueList* dummyList = new DialogueList();
  dummyList->addBack(chosenRoot);
  DialogueRunner runner( raiser, dummyList );

  //Finally run the dialogue
  while(!runner.isFinished()){
    npcSpeak(runner.npcSpeech());
    cout << "How do you respond?" << endl;
    for( int i=0; i<runner.numOptions(); i++ ){
      cout << "\t" << i << ".) " << runner.getOption(i) << endl;
    }
    runner.chooseOption(getInt(runner.numOptions()-1));
    cout << endl;
  }
  npcSpeak(runner.npcSpeech()); //final goodbye
}

