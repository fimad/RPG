#ifndef _PROXY_MODIFIER_HPP_
#define _PROXY_MODIFIER_HPP_

#include "character/Modifier.hpp"

class ProxyModifier : public Modifier {
  public:
    ProxyModifier(const string& description, Modifier* modifier);
    virtual int valueFor(Stats::Stat stat);
  private:
    Modifier* _modifier;
};

#endif

