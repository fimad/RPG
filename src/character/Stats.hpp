#ifndef _ATTRIBUTES_HPP_
#define _ATTRIBUTES_HPP_

#include <string>
#include <map>
#include "resources/XmlResource.hpp"
using namespace std;

//When saving/reading from an xml file the current modifiers should not be included
//They should be readded by the character.
//This is because items and the like will need to remove the modifier when they are not worn,
//and if the attribute creates the modifier the item would no longer have a reference to it
class Modifier;
class Stats : public XmlResource{
  public:
    enum Stat{
      //6 Ability Scores, (the total score)
        STR = 0
      , DEX
      , CON
      , INT
      , WIS
      , CHA
      //Ability modifiers (the modifier associated with the score)
      , STR_MOD
      , DEX_MOD
      , CON_MOD
      , INT_MOD
      , WIS_MOD
      , CHA_MOD
      //Saving Throws
      , FORTITUDE
      , REFLEX
      , WILL
      //Misc Attributes
      , MAX_HP
      , MAX_MP
      , HP_PER_SEC
      , MP_PER_SEC
      , ARMOR_CLASS
      , ARMOR_CLASS_FLAT
      , ARMOR_CLASS_TOUCH
      , ATTACK_BONUS
      , RANGED_ATTACK_BONUS
      , SPEED
      //Skills
      //NUM_STATS should always be last
      , NUM_STATS
    };

    Stats();
    int getStat(Stat stat) const;
    int getBaseStat(Stat stat) const;
    //Will only work for stats that aren't calculated from other stats
    void setBaseStat(Stat stat, int value);
    void addModifier(Modifier* modifier);
    void removeModifier(Modifier* modifier);

    static const string& getString(Stat stat);
    static bool getStatForString(const string& str, Stat* stat);

    friend class XmlResource;
  private:
    int _baseStats[NUM_STATS];
    list<Modifier*> _modifiers;

    static int __getBaseStat(const Stats* stats, Stat stat);
    static int __getAbilityStat(const Stats* stats, Stat stat); //calcs for strength, etc
    template <Stat>
    static int __dependentStat(const Stats* stats, Stat stat);
    static int (* _calcStats[])(const Stats*,Stat);
    static string _statToString[];
    static map<string,Stat> _stringToStat;
};
MAKE_XML_RESOURCE(Stats)

#endif

