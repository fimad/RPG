#ifndef _LUA_WRAPPER_HPP_
#define _LUA_WRAPPER_HPP_

#include <SLB/SLB.hpp>
#include <SLB/Object.hpp>
#include <string>
using namespace std;

class LuaWrapper{
  public:
    //exports classes and functions to lua
    static void setup();
    //destroy's the current lua instance
    static void reset();

    //TODO: implement error reporting
    //you could probably make a new LuaException class
    //set SLB to throw exceptions, catch them in these, and then rethrow the better LuaException
    static void doString(const string& lua);
    static void doFile(const string& fileName);

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

#endif

