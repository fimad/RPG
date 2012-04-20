#include "resources/ResourceDefs.hpp"
#include "resources/Path.hpp"

//ResourceException
string ResourceException::description() const throw(){
  return "A resource exception has occurred!";
}

//NoSuchPathException
NoSuchPathException::NoSuchPathException(const string& path){
  this->path = path;
}

NoSuchPathException::NoSuchPathException(const Path& path){
  this->path = path.toString();
}

NoSuchPathException::~NoSuchPathException() throw(){}

string NoSuchPathException::description() const throw(){
  return "No such path: '"+path+"'!";
}

//InvalidPathComponentException
InvalidPathComponentException::InvalidPathComponentException(const string& comp){
  component = comp;
}

InvalidPathComponentException::~InvalidPathComponentException() throw(){}

string InvalidPathComponentException::description() const throw(){
  return "Invalid path component: '"+component+"'!";
}

//MalformedResourceException
MalformedResourceException::MalformedResourceException(const Path& path, const string& details) : _path(path){
  _details = details;
}

MalformedResourceException::~MalformedResourceException() throw(){}

string MalformedResourceException::description() const throw(){
  return "Path: '"+_path.toString()+"': Malformed resource: "+_details+"!";
}

