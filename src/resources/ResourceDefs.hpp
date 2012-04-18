#ifndef _RESOURCE_DEFS_HPP_
#define _RESOURCE_DEFS_HPP_

#include "Errors.hpp"

typedef unsigned char byte;

class ResourceException : public Exception{
  virtual string description() const throw();
};

class Path;
class NoSuchPathException : public ResourceException{
  public:
    NoSuchPathException(const string& path);
    NoSuchPathException(const Path& path);
    ~NoSuchPathException() throw();
    virtual string description() const throw();
  private:
    string path;
};

class InvalidPathComponentException : public ResourceException{
  public:
    InvalidPathComponentException(const string& comp);
    ~InvalidPathComponentException() throw();
    virtual string description() const throw();
  private:
    string component;
};

#endif

