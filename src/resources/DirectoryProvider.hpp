#ifndef _DIRECTORY_PROVIDER_HPP_
#define _DIRECTORY_PROVIDER_HPP_

#include "resources/ResourceProvider.hpp"

class DirectoryProvider : public ResourceProvider {
  public:
    DirectoryProvider(string root);
    virtual bool provides(const Path& path);
    virtual string getBuffer(const Path& path);
    virtual void putBuffer(const Path& path, string buffer);
  private:
    string rootDirectory;
};

#endif

