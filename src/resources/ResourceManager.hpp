#ifndef _RESOURCE_MANAGER_HPP_
#define _RESOURCE_MANAGER_HPP_

#include <list>
#include <map>
#include "resources/ResourceProvider.hpp"
#include "resources/Resource.hpp"
using namespace std;

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
//      Resource* not_subclass_of_Resource = (T*)0; //error if we pass something that is not a resource

      for(auto i = providers.begin(); i!=providers.end(); i++){
        if((*i)->provides(path)){
          char* buffer = (*i)->getBuffer(path);
          T* resource = Resource::load<T>(path,buffer,this);
          free(buffer);
          //not everything we load will be a subclass of Resource, if it is thought, set the fields
          Resource* r;
          if( (r=dynamic_cast<Resource*>(resource)) != 0){
            r->_manager = this;
            r->_path = path;
          }
          return resource;
        }
      }
      raise(NoSuchPathException,path);
    }

    //caller is responsible for freeing the buffer
    char* getBuffer(const Path& path){
      for(auto i = providers.begin(); i!=providers.end(); i++){
        if((*i)->provides(path)){
          return (*i)->getBuffer(path);
        }
      }
      return NULL;
    }

  private:
    list<ResourceProvider*> providers;
    map<Path,Resource*> resourceCache;
};

#endif

