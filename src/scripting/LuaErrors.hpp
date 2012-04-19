#ifndef _LUA_EXCEPTION_HPP_
#define _LUA_EXCEPTION_HPP_

#include "Errors.hpp"

class LuaException : public Exception{
  public:
    LuaException(const string& desc);
    ~LuaException() throw();
    string description() const throw();
  private:
    string error;
};

#endif

