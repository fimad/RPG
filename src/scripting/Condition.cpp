#include "scripting/Condition.hpp"
#include "scripting/LuaWrapper.hpp"

const Condition Condition::AlwaysAllow = Condition("true");
const Condition Condition::AlwaysDeny = Condition("false");

Condition::Condition(const string& luaExpr) : _luaExpr(luaExpr){
}

bool Condition::allows() const{
  return LuaWrapper::evaluate<bool>(_luaExpr);
}

