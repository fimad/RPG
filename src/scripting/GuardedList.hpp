#ifndef _GUARDED_LIST_HPP_
#define _GUARDED_LIST_HPP_

#include <list>
#include <algorithm>
#include "scripting/GuardedObject.hpp"
using namespace std;

class GuardedObject;
template<class T>
class GuardedList{
  public:
    GuardedList(){
      //attempt to enforce the use of subclasses of GuardedObject
      GuardedObject* class_is_not_sub_class_of_GuardedObject = (T*)0;
    }
    int size() const{ return _objects.size(); }
    void addFront(T* object){ _objects.push_front(object); }
    void addBack(T* object){ _objects.push_back(object); }
    void remove(T* object){ _objects.remove(object); }

    T* getFirst() const{
      return (*( find_if(_objects.begin(),_objects.end(),
        [](GuardedObject* obj) -> bool {return obj->isAllowed();}
      ) ));
    }

    T* operator*() const{
      return getFirst();
    }

    list<T*> getAll() const{
      list<T*> buffer(_objects);
      list<T*> result(buffer.begin(),
        remove_if( buffer.begin(), buffer.end(),
          [](GuardedObject* obj) -> bool {return !obj->isAllowed();}
        )
      );
      return result;
    }

  private:
    list<T*> _objects;
};

#endif

