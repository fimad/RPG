#ifndef _RESOURCE_HPP_
#define _RESOURCE_HPP_

#include <string>
#include "resources/Path.hpp"
#include "scripting/EventRaiser.hpp"
using namespace std;

//There is no way to enforce this in cxx, but if you want a useable subclass of Resource
//You also need to define a static T* loadFromBuffer(string) method
//This is used by ResourceManager to load the object from a file, it will yell at you if you don't
//but the error messages won't be pretty :P

class ResourceManager;
class Resource : public EventRaiser{
  public:
    Resource();
    virtual ~Resource();
    const Path& getPath();
    //static Resource* loadFromBuffer(string buffer);
    //virtual string saveToBuffer() = 0; //on second thought, I don't think I need this
    friend class ResourceManager;
  private:
    ResourceManager* manager;
    Path path;
};

#endif

