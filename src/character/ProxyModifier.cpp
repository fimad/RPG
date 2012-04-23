#include "character/ProxyModifier.hpp"

ProxyModifier::ProxyModifier(const string& description, Modifier* modifier)
  : Modifier(description)
  , _modifier(modifier)
{
}

int ProxyModifier::valueFor(Stats::Stat stat){
  return _modifier->valueFor(stat);
}

