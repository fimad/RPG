#ifndef _CHARACTER_CLASS_HPP_
#define _CHARACTER_CLASS_HPP_

#include <vector>
#include <string>
#include "resources/XmlResource.hpp"
using namespace std;

/*
TODO:
Requires specific conditions:
  -conditional classes, ie. prestige classes with requirements
Requires actions:
  -class feats
*/

class Stats;
class Modifier;
class ProxyModifier;
class CharacterClass : public XmlResource{
  public:
    CharacterClass(const string& name, const string& desc, const list<Modifier*> modifiers, int level=1);
    ~CharacterClass();
    const string& getName() const;
    const string& getDescription() const;
    Modifier* getModifier() const;
    void setLevel(int level);
    void levelUp();
    bool canLevelUp();
    int currentLevel();
    int maxLevel();
  private:
    string _name;
    string _description;
    int _currentLevel;
    int _maxLevel;
    ProxyModifier* _proxyModifier;
    vector<Modifier*> _modifiers;
};
MAKE_XML_RESOURCE(CharacterClass)

#endif

