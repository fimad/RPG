#ifndef _SPELL_HPP_
#define _SPELL_HPP_

#include <SLB/SLB.hpp>
#include <string>
#include "resources/XmlResource.hpp"
using namespace std;

class Character;
class Tile;

class Spell : public XmlResource{
  public:
    Spell(const string& name, const string& description, const string& effect);
    const string& getName();
    const string& getDescription();
    int cast(Character* caster,Tile* target); //returns mana drained
  private:
    string _name;
    string _description;
    SLB::LuaCall<int(Character*,Tile*)> _effect;
};
MAKE_XML_RESOURCE(Spell)

#endif 

