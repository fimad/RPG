#ifndef _EVENT_MANAGER_HPP_
#define _EVENT_MANAGER_HPP_

#include <map>
#include <set>
#include <tuple>
#include "resources/Path.hpp"
#include "scripting/EventRaiser.hpp"
using namespace std;

class GenericEvent;
class EventHandler;
class EventManager {
  public:
    static EventManager* global(); //returns a singleton reference
    static void destroy(); //destroy's the current singleton reference (restarting, etc)
    void subscribe(EventHandler* handler, Path raiser);
    void unsubscribe(EventHandler* handler);

    friend class EventRaiser;
  private:
    void raiseEvent(Path raiser, GenericEvent* type);
    EventManager();

    static EventManager* instance;
    map<Path,set<EventHandler*>> eventToHandler;
    map<EventHandler*,set<Path>> handlerToEvent;
};

#endif

