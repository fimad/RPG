#ifndef _LUA_WRAPPER_HPP_
#define _LUA_WRAPPER_HPP_

#include <SLB/SLB.hpp>
#include <SLB/Object.hpp>
#include <string>
#include "scripting/LuaErrors.hpp"
#include "resources/XmlResource.hpp"
using namespace std;

class LuaWrapper{
  public:
    typedef string LuaSrc;

    //exports classes and functions to lua
    static void setup();
    //destroy's the current lua instance
    static void reset();

    //TODO: implement error reporting
    //you could probably make a new LuaException class
    //set SLB to throw exceptions, catch them in these, and then rethrow the better LuaException
    static void doString(const string& lua);
    static void doFile(const string& fileName);

    //a wrapper for SLB::CallLua class
    //TODO: better error handling for when the lua environment is not setup
    template<class Result, class ... Args>
    static Result callLua(const string& func, const Args&... args){
      if( !script )
        raise(LuaException,"Lua not initialized!");
      SLB::LuaCall<Result(Args...)> call(script->getState(), func.c_str());
      return call(args...);
    }

    template<class Result>
    static Result evaluate(const string& lua){
      return callLua<bool,string>("evaluate", "return "+lua);
    }

    //This will generate a LuaCall that will call the function created by the lua_func string
    //The lua_func string must be formated as an anonymous function, like so:
    /*
       function (...)
          ...
          return ...
       end
     */
    template<typename Result,typename... Args>
    static SLB::LuaCall<Result(Args...)> makeLuaFunc(const string& lua_func){
      if( !script )
        raise(LuaException,"Lua not initialized!");
      lua_State* L = script->getState();

      //call evaluate and return the anonymous function
      lua_getglobal(L, "evaluate");
      lua_pushstring(L, ("return "+lua_func).c_str());
      if (lua_pcall(L, 1, 1, 0) != 0)
        raise(LuaException,"Error creating function: \n"+lua_func+"\nBecause: "+lua_tostring(L,-1));

      //pass the function to LuaCall :D
      return SLB::LuaCall<Result(Args...)>(L,-1);
    }

    static void printCallback_stderr(SLB::Script*,const char*,size_t);

    //exports a value to the global namespace
    /*
    template<class T>
    static void exportValue(const string& name, T value){
        SLB::Manager::defaultManager()->set(name.c_str(),SLB::slb_dynamic_cast<SLB::Object*,T>(value));
        doString(name+" = SLB."+name); //copy it into the global namespace
    }*/

  private:
    static void exportApi(SLB::Manager* m); //actuall exports classes

    static SLB::Script* script;
};
MAKE_XML_RESOURCE(LuaWrapper::LuaSrc)

#endif

