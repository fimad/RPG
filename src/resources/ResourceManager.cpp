#include "resources/ResourceManager.hpp"
#include "resources/ResourceProvider.hpp"
#include "resources/ResourceDefs.hpp"
#include "resources/Path.hpp"
#include "Errors.hpp"

ResourceManager::ResourceManager(){
}

ResourceManager::~ResourceManager(){
  while(!providers.empty()){
    delete providers.front();
    providers.pop_front();
  }
}

void ResourceManager::addProvider(ResourceProvider* provider){
  providers.push_front(provider);
}

void ResourceManager::preloadResource(const Path& path){
  //TODO:actually preload resources
}

