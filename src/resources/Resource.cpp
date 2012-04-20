#include "resources/Resource.hpp"

Resource::Resource() : path(Path::Any){
  manager = NULL;
}

Resource::~Resource(){
}

const Path& Resource::getPath(){
  return path;
}
