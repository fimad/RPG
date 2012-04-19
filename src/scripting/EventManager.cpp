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
    //remove handler from each set in eventToHandler
    for(Path p : handlerToEvent[handler]){
      eventToHandler[p].erase(handler);
    }
    handlerToEvent.erase(handler);
  }
}

void EventManager::raise(Path raiser, GenericEvent* type){
  if( eventToHandler.count(raiser) ){
    for(EventHandler* handler : eventToHandler[raiser]){
      handler->handleEvent(raiser,type);
    }
  }
}

