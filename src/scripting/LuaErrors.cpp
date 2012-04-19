#include "scripting/LuaErrors.hpp"

LuaException::LuaException(const string& desc){
  error = desc;
}

LuaException::~LuaException() throw(){
}

string LuaException::description() const throw(){
  return error;
}

