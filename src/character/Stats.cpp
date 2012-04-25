#include "character/Stats.hpp"
#include "character/Modifier.hpp"

//TODO:Add more stats and their corresponding calculators

int Stats::__getBaseStat(const Stats* stats, Stat stat){
  return stats->_baseStats[stat];
}
int Stats::__getAbilityStat(const Stats* stats, Stat stat){
  int base = stats->getStat((Stat)(stat-6));
  return (base >= 10) ? (base-10)/2 : (base-11)/2;
}
template <Stats::Stat dstat>
int Stats::__dependentStat(const Stats* stats, Stat stat){
  return stats->_baseStats[stat]+stats->getStat(dstat);
}

int(* Stats::_calcStats[])(const Stats*, Stats::Stat) = {
    &Stats::__getBaseStat
  , &Stats::__getBaseStat
  , &Stats::__getBaseStat
  , &Stats::__getBaseStat
  , &Stats::__getBaseStat
  , &Stats::__getBaseStat
  //Ability modifiers (the modifier associated with the score)
  , &Stats::__getAbilityStat
  , &Stats::__getAbilityStat
  , &Stats::__getAbilityStat
  , &Stats::__getAbilityStat
  , &Stats::__getAbilityStat
  , &Stats::__getAbilityStat
  //Saving Throws
  , &Stats::__dependentStat<CON_MOD> //fort
  , &Stats::__dependentStat<DEX_MOD> //reflex
  , &Stats::__dependentStat<WIS_MOD> //will
  //Misc Attributes
  , &Stats::__getBaseStat
  , &Stats::__getBaseStat
  , &Stats::__getBaseStat
  , &Stats::__getBaseStat
  , &Stats::__getBaseStat //Armor Class
  , &Stats::__getBaseStat //Armor Class flat footed
  , &Stats::__getBaseStat //Armor Class touch
  , &Stats::__getBaseStat //Attack Bonus
  , &Stats::__getBaseStat //Ranged Attack Bonus
  , &Stats::__getBaseStat //Speed
};

bool Stats::getStatForString(const string& str, Stat* stat){
  if( _stringToStat.count(str) == 0 ){
    return false;
  }else{
    *stat = _stringToStat[str];
    return true;
  }
}
map<string,Stats::Stat> Stats::_stringToStat{
    {"str", Stats::STR}
  , {"dex", Stats::DEX}
  , {"con", Stats::CON}
  , {"int", Stats::INT}
  , {"wis", Stats::WIS}
  , {"cha", Stats::CHA}
  //Ability modifiers (the modifier associated with the score)
  , {"str_mod", Stats::STR_MOD}
  , {"dex_mod", Stats::DEX_MOD}
  , {"con_mod", Stats::CON_MOD}
  , {"int_mod", Stats::INT_MOD}
  , {"wis_mod", Stats::WIS_MOD}
  , {"cha_mod", Stats::CHA_MOD}
  //Saving Throws
  , {"fortitude", Stats::FORTITUDE}
  , {"reflex", Stats::REFLEX}
  , {"will", Stats::WILL}
  //Misc Attributes
  , {"hp", Stats::MAX_HP}
  , {"mp", Stats::MAX_MP}
  , {"hp_regen", Stats::HP_PER_SEC}
  , {"mp_regen", Stats::MP_PER_SEC}
  , {"ac", Stats::ARMOR_CLASS}
  , {"ac_flat", Stats::ARMOR_CLASS_FLAT}
  , {"ac_touch", Stats::ARMOR_CLASS_TOUCH}
  , {"attack", Stats::ATTACK_BONUS}
  , {"ranged_attack", Stats::RANGED_ATTACK_BONUS}
  , {"speed", Stats::SPEED}
};

string Stats::_statToString[] = {
  //Ability scores
    "strength"
  , "dexterity"
  , "constitution"
  , "intelligence"
  , "wisdom"
  , "charisma"
  //ability modifiers
  , "strength"
  , "dexterity"
  , "constitution"
  , "intelligence"
  , "wisdom"
  , "charisma"
  //Saving Throws
  , "fortitude"
  , "reflex"
  , "will"
  //Misc Attributes
  , "max HP"
  , "max MP"
  , "regained HP per second"
  , "regained MP per second"
  , "armor class"
  , "armor class (flat footed)"
  , "armor class (touch)"
  , "attack bonus"
  , "ranged attack bonus"
  , "speed"
};

const string& Stats::getString(Stat stat){
  return _statToString[stat];
}

Stats::Stats(){
  //set all base stats to 0
  for(int i; i<NUM_STATS; i++){
    _baseStats[i] = 0;
  }
}

int Stats::getStat(Stat stat) const{
  int base = getBaseStat(stat);
  for(Modifier* m : _modifiers){
    base += m->valueFor(stat);
  }
  return base;
}

int Stats::getBaseStat(Stat stat) const{
  return _calcStats[stat](this,stat);
}

void Stats::setBaseStat(Stat stat, int value){
  _baseStats[stat] = value;
}

void Stats::addModifier(Modifier* modifier){
  _modifiers.push_back(modifier);
}

void Stats::removeModifier(Modifier* modifier){
  _modifiers.remove(modifier);
}

//TODO: load xml for Stats
DEF_XML_RESOURCE_LOAD(Stats){
  return NULL;
}

