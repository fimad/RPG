#include "resources/ResourceDefs.hpp"
#include "resources/Path.hpp"

//ResourceException
string ResourceException::description() const throw(){
  return where()+"A resource exception has occurred!";
}

//NoSuchPathException
NoSuchPathException::NoSuchPathException(const string& path){
  this->path = path;
}

NoSuchPathException::NoSuchPathException(const Path& path){
  this->path = path.toString();
}

NoSuchPathException::~NoSuchPathException() throw(){
}

string NoSuchPathException::description() const throw(){
  return where()+"No such path: '"+path+"'!";
}

//InvalidPathComponentException
InvalidPathComponentException::InvalidPathComponentException(const string& comp){
  component = comp;
}

InvalidPathComponentException::~InvalidPathComponentException() throw(){
}

string InvalidPathComponentException::description() const throw(){
  return where()+"Invalid path component: '"+component+"'!";
}
