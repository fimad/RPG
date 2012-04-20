#include "scripting/EventRaiser.hpp"
#include "scripting/EventHandler.hpp"
#include "scripting/GenericEvent.hpp"
#include "resources/Path.hpp"

class DummyRaiser : public EventRaiser {
  public:
    DummyRaiser(const string& path):_path(path) {}
    DummyRaiser(const Path& path):_path(path) {}
    const Path& getPath(){
      return _path;
    }
  private:
    Path _path;
};

class DummyHandler : public EventHandler {
  public:
    DummyHandler(GenericEvent* type) : _didHandle(false), _type(type){}
    ~DummyHandler(){
      delete _type;
    }
    void handleEvent(Path raiser, GenericEvent* type){
      if( _type->equals(type) ){
        _didHandle = true;
      }
    }
    bool didHandle(){
      return _didHandle;
    }
  private:
    GenericEvent* _type;
    bool _didHandle;
};
