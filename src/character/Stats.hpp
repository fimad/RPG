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
        STRENGTH_SCORE = 0
      , DEXTERITY_SCORE
      , CONSTITUTION_SCORE
      , INTELLIGENCE_SCORE
      , WISDOM_SCORE
      , CHARISMA_SCORE
      //Ability modifiers (the modifier associated with the score)
      , STRENGTH
      , DEXTERITY
      , CONSTITUTION
      , INTELLIGENCE
      , WISDOM
      , CHARISMA
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
      , BASE_ATTACK_BONUS
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
  private:
    int _baseStats[NUM_STATS];
    list<Modifier*> _modifiers;

    static int __getBaseStat(const Stats* stats, Stat stat);
    static int __getAbilityStat(const Stats* stats, Stat stat); //calcs for strength, etc
    static int (* _calcStats[])(const Stats*,Stat);
    static string _statToString[];
    //TODO: _stringToStat
//    static map<string,Stat> _stringToStat;
};
MAKE_XML_RESOURCE(Stats)

#endif

