#ifndef _RESOURCE_PROVIDER_HPP_
#define _RESOURCE_PROVIDER_HPP_

#include "resources/ResourceDefs.hpp"

class ResourcePath;

class ResourceProvider{
  public:
    virtual bool provides(const Path& path) = 0;
    virtual string getBuffer(const Path& path) = 0;
    virtual void putBuffer(const Path& path, string buffer) = 0;
};

#endif

