#ifndef _GENERIC_EVENT_HPP_
#define _GENERIC_EVENT_HPP_

//used in the equals method to assign the parameter to a pointer of the current type
//and return false if it is not possible to do so
#define event_test_and_set(type,newvar,totest) \
  type (newvar) = dynamic_cast<type>(totest);\
  if( (newvar) == NULL ) return false;


class GenericEvent {
  protected:
    GenericEvent();
  public:
    virtual bool equals(const GenericEvent*);
};

#endif

