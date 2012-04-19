#ifndef _CONDITION_HPP_
#define _CONDITION_HPP_

#include <string>
using namespace std;

class Condition{
  public:
    Condition(const string& luaExpr);
    bool allows() const;

    static const Condition AlwaysAllow;
    static const Condition AlwaysDeny;
  private:
    string _luaExpr;
};

#endif

