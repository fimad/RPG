#ifndef _RESOURCE_MANAGER_HPP_
#define _RESOURCE_MANAGER_HPP_

#include <list>
#include <map>
#include "resources/ResourceProvider.hpp"
using namespace std;

class Resource;
class Path;

class ResourceManager{
  public:
    ResourceManager();
    ~ResourceManager();
    void addProvider(ResourceProvider* provider); //The resource manager will own the provider
    void preloadResource(const Path& path);

    //TODO: add cacheing
    template<class T>
    T* loadResource(const Path& path){
      //hacks to get semi reasonable error messages when passing in non-compliant types
      Resource* not_subclass_of_Resource = (T*)0; //error if we pass something that is not a resource
      void* did_not_define_loadFromBuffer = (void*)&T::loadFromBuffer; //error if loadFromBuffer is not defined

      for(auto i = providers.begin(); i!=providers.end(); i++){
        if((*i)->provides(path)){
          T* resource = T::loadFromBuffer((*i)->getBuffer(path));
          resource->manager = this;
          return resource;
        }
      }
      raise(NoSuchPathException,path);
    }

  private:
    list<ResourceProvider*> providers;
    map<Path,Resource*> resourceCache;
};

#endif

