#include <iostream>
#include "scripting/LuaWrapper.hpp"
#include "scripting/LuaErrors.hpp"

#include "scripting/EventHandler.hpp"
#include "scripting/GuardedObject.hpp"
#include "scripting/GenericEvent.hpp"
#include "scripting/EventManager.hpp"
#include "scripting/EventRaiser.hpp"
#include "scripting/StringEvent.hpp"
#include "scripting/GuardedList.hpp"
#include "scripting/Condition.hpp"
#include "plot/DialogueEvent.hpp"
#include "resources/Path.hpp"

SLB::Script* LuaWrapper::script = NULL;

void LuaWrapper::reset(){
  if( script ){
    delete script;
    script = NULL;
  }
  SLB::Manager::destroyDefaultManager();
}

void LuaWrapper::setup(){
  //grab a new instance of script
  script = new SLB::Script();
  script->setPrintCallback(&printCallback_stderr);

  exportApi(SLB::Manager::defaultManager());

  doString("SLB.using(SLB.Barrel)");
  doString(" \
    function evaluate(x) \
      return load(x)() \
    end \
  ");
}

void LuaWrapper::printCallback_stderr(SLB::Script* script, const char* error, size_t size){
  cerr << "LuaError: " << string(error,size) << endl;
}

void LuaWrapper::doString(const string& lua){
  if( !script )
    raise(LuaException,"Lua not initialized!");
  try{
    script->doString(lua.c_str());
  }catch(exception& e){
    throw LuaException(e.what());
  }
}

void LuaWrapper::doFile(const string& fileName){
  if( !script )
    raise(LuaException,"Lua not initialized!");
  try{
    script->doFile(fileName.c_str());
  }catch(exception& e){
    throw LuaException(e.what());
  }
}

void LuaWrapper::exportApi(SLB::Manager* m){
  SLB::Class<Path>("Barrel::Path",m)
    .constructor<const string&>()
    .set("Any", &Path::Any)
    .const_set("split", &Path::split)
    .const_set("up", &Path::up)
    .const_set("down", (Path (Path::*)(const string&) const)&Path::down)
    .const_set("append", (Path (Path::*)(const Path&) const)&Path::down)
    .const_set("matches", &Path::matches)
    .const_set("toString", &Path::toString)
  ;

  //the NoCopy is needed because EventRaiser contains a pure virtual method
  SLB::Class<EventRaiser, SLB::Instance::NoCopy>("Barrel::EventRaiser",m)
    .set("getPath", &EventRaiser::getPath)
    .set("raiseEvent", &EventRaiser::raiseEvent)
  ;

  SLB::Class<EventHandler, SLB::Instance::NoCopy>("Barrel::EventHandler",m)
    .set("handleEvent", &EventHandler::handleEvent)
  ;

  SLB::Class<EventManager>("Barrel::EventManager",m)
    .set("subscribe", &EventManager::subscribe)
    .set("unsubscribe", &EventManager::unsubscribe)
  ;

  SLB::Class<GenericEvent>("Barrel::GenericEvent",m)
    .set("equals", &GenericEvent::equals)
  ;

  SLB::Class<StringEvent>("Barrel::StringEvent",m)
    .inherits<GenericEvent>()
    .constructor<const string&>()
    .set("equals", &StringEvent::equals)
    .set("value", &StringEvent::value)
  ;

  SLB::Class<DialogueEvent>("Barrel::DialogueEvent",m)
    .inherits<GenericEvent>()
    .constructor<const string&>()
    .set("equals", &DialogueEvent::equals)
    .set("value", &DialogueEvent::value)
  ;
  
  SLB::Class<Condition>("Barrel::Condition",m)
    .constructor<const string&>()
    .set("AlwaysAllow", &Condition::AlwaysAllow)
    .set("AlwaysDeny", &Condition::AlwaysDeny)
    .set("allows", &Condition::allows)
  ;
  
  SLB::Class<GuardedObject>("Barrel::GuardedObject",m)
    .set("isAllowed", &GuardedObject::isAllowed)
    .set("setCondition", &GuardedObject::setCondition)
    .set("getCondition", &GuardedObject::getCondition)
  ;

  //not sure how inheritance will work with templated classes
  //we may need to add one of these definitions for each type
  SLB::Class<GuardedList<GuardedObject>>("Barrel::GuardedList",m)
  ;
}

