#include "scripting/EventManager.hpp"
#include "scripting/EventHandler.hpp"

EventManager* EventManager::instance = NULL;

EventManager::EventManager(){}

EventManager* EventManager::global(){
  if( !instance ){
    instance = new EventManager();
  }
  return instance;
}

void EventManager::destroy(){
  if( instance ){
    delete instance;
    instance = NULL;
  }
}

void EventManager::subscribe(EventHandler* handler, Path raiser){
  //update eventToHandler
  if( eventToHandler.count(raiser) ){
    eventToHandler[raiser].insert(handler);
  }else{
    set<EventHandler*> newSet;
    newSet.insert(handler);
    eventToHandler[raiser] = newSet;
  }
  //update handlerToEvent
  if( handlerToEvent.count(handler) ){
    handlerToEvent[handler].insert(raiser);
  }else{
    set<Path> newSet;
    newSet.insert(raiser);
    handlerToEvent[handler] = newSet;
  }
}

void EventManager::unsubscribe(EventHandler* handler){
  if( handlerToEvent.count(handler) ){
    auto eventSet = handlerToEvent[handler];
    //remove handler from each set in eventToHandler
    for(auto it=eventSet.begin(); it!=eventSet.end(); it++){
      eventToHandler[*it].erase(handler);
    }
    handlerToEvent.erase(handler);
  }
}

void EventManager::raise(Path raiser, GenericEvent* type){
  if( eventToHandler.count(raiser) ){
    auto handlerSet = eventToHandler[raiser];
    for(auto it=handlerSet.begin(); it!=handlerSet.end(); it++){
      (*it)->handleEvent(raiser,type);
    }
  }
}

