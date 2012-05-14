#include "resources/Resource.hpp"

Resource::Resource() : _path(Path::Any){
  _manager = NULL;
}

Resource::~Resource(){
}

const Path& Resource::getPath(){
  return _path;
}

ResourceManager* Resource::getManager() const{
  return _manager;
}

