#ifndef _RESOURCE_HPP_
#define _RESOURCE_HPP_

#include <string>
#include "resources/Path.hpp"
#include "scripting/EventRaiser.hpp"
using namespace std;

//Macros that make it "easy" to make new Resources
#define BEGIN_RESOURCE(className) _DEF_RESOURCE(className,public Resource)
#define BEGIN_RESOURCE_INHERITS(className,...) _DEF_RESOURCE(className,public Resource,__VA_ARGS__)
#define _DEF_RESOURCE(className,...) class className : __VA_ARGS__ {

#define END_RESOURCE(className) \
}; \
template <> class className* Resource::load<className>(const Path& path,char* buffer);

#define DEF_RESOURCE_LOAD(className) \
template <> class className* Resource::load<className>(const Path& path,char* buffer)

class ResourceManager;
class Resource : public EventRaiser{
  public:
    Resource();
    virtual ~Resource();
    const Path& getPath();
    //virtual string saveToBuffer() = 0; //on second thought, I don't think I need this

    //All Resources must provide a specialization for this function
    template<class T>
    static T* load(const Path& path, char* node);

    friend class ResourceManager;
  private:
    ResourceManager* manager;
    Path path;
};

#endif

