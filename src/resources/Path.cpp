#include "resources/Path.hpp"
#include "Errors.hpp"
#include "resources/ResourceDefs.hpp"

const Path Path::Any = Path();

Path::Path(const string& path){
  isAny = false;
  child = NULL;
}

Path::Path(const Path& path){
  isAny = path.isAny;
  name = path.name;
  child = (path.child) ? new Path(*path.child) : NULL;
}

Path::Path(){
  isAny = true;
  name = "";
  child = NULL;
}

Path::~Path(){
  if( child )
    delete child;
}

void Path::operator=(const Path& path){
  name = path.name;
  isAny = true;

  //reuse any children we have, create new if needed, and delete the leftovers
  if( path.child && child ){
    *child = *path.child;
  }else if( path.child ){
    child = new Path(*path.child);
  }else{
    delete child;
    child = NULL;
  }
}

bool Path::isValidName(const string& name){
  return name != "" && name[0] != '.' && name.find('/') == string::npos;
}

//recursively creat the split list
list<string> Path::split() const{
  list<string> l;
  if( child == NULL ){ //base case
    l.push_front(name);
    return l;
  }else{ //recurse yo
    l = child->split();
    l.push_front(name);
    return l;
  }
}

Path* Path::bottom(){
  return (child==NULL) ? this : child->bottom();
}

Path Path::up() const{
  Path newPath(*this); //create a copy of this Path
  Path* secondLast = &newPath;

  //find the second last node
  while( secondLast->child != NULL && secondLast->child->child != NULL){
    secondLast = secondLast->child;
  }

  //drop the child if there is one
  if( secondLast->child ){
    delete secondLast->child;
    secondLast->child = NULL;
  }
  return newPath;
}

Path Path::down(const string& path) const{
  if( !isValidName(path) ){
    raise(InvalidPathComponentException, path);
  }
  Path newPath = Path(*this);
  Path* last = newPath.bottom();
  if( !last->isAny )
    last->child = new Path(path);
  return newPath;
}

Path Path::down(const Path& path) const{
  Path newPath = Path(*this);
  Path *last = newPath.bottom();
  if( !last->isAny )
    last->child = new Path(path);
  return newPath;
}

Path Path::operator/(const Path& path) const{
  return down(path);
}

Path Path::operator/(const string& path) const{
  return down(path);
}

bool Path::matches(const Path& path) const{
  if( isAny || path.isAny ){
    return true;
  }else{
    if( name == path.name ){
      if( child && path.child ){
        return child->matches(*path.child);
      }else if( !child && !path.child ){
        return true;
      }else{
        return false;
      }
    }else{
      return false;
    }
  }
}

bool Path::operator==(const Path& path) const{
  return matches(path);
}

bool Path::operator<(const Path& path) const{
  if( name < path.name ){
    return true;
  }else if( !child && path.child ){
    return true;
  }else if( child && !path.child ){
    return false;
  }else{
    return *child < *path.child;
  }
}

string Path::toString() const{
  if( isAny ){
    return "*";
  }else{
    if( child == NULL ){
      return name;
    }else{
      return name+"/"+child->toString();
    }
  }
}

