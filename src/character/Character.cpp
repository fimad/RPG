#include "character/Character.hpp"
#include "character/CharacterClass.hpp"
#include "character/ProxyModifier.hpp"
#include "character/Stats.hpp"
#include "character/Race.hpp"
#include <algorithm>
using namespace std;

Character::Character(const string& name, Race* race, CharacterClass* startingClass, Stats* initialStats)
  : _name(name)
  , _race(race)
  , _exp(0)
{
  if( initialStats == NULL ){
    _stats = new Stats();
  }else{
    _stats = initialStats;
  }
  _classes.push_front(startingClass);

  //populate the _stats with the appropriate modifiers
  _stats->addModifier(startingClass->getModifier());
  _stats->addModifier(_race->getModifier());

  //fill the hp and mp to max
  fillHP();
  fillMP();
}

Character::~Character(){
  delete _stats;
  delete _race;
  for( CharacterClass* c : _classes ){
    delete c;
  }
}

int Character::getHP() const{
  return _hp;
}

int Character::getMP() const{
  return _mp;
}

//TODO: handle death, raise an event. Not sure what else. Maybe just that. 
void Character::takeDamage(int amount){
  _hp -= max(amount,0);
}

void Character::useMP(int amount){
  _mp -= max(amount,0);
}

void Character::addHP(int amount){
  _hp = min(_hp+amount, _stats->getStat(Stats::MAX_HP));
}

void Character::addMP(int amount){
  _mp = min(_mp+amount, _stats->getStat(Stats::MAX_MP));
}

//TODO: events for leveling up?
void Character::addExp(int amount){
  _exp += amount;
}

void Character::step(double delta){
  //replenish mp over time
  //TODO: if you have regen < 1 per sec, you won't regain any. Fix this.
  addMP(_stats->getStat(Stats::MP_PER_SEC)*delta);
  addHP(_stats->getStat(Stats::HP_PER_SEC)*delta);
}

void Character::fillHP(){
  _hp = _stats->getStat(Stats::MAX_HP);
}

void Character::fillMP(){
  _mp = _stats->getStat(Stats::MAX_MP);
}

Stats* Character::getStats(){
  return _stats;
}

//TODO:load from xml...
DEF_XML_RESOURCE_LOAD(Character){
  return NULL;
}

