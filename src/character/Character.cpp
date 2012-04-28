#include "character/Character.hpp"
#include "character/CharacterClass.hpp"
#include "character/ProxyModifier.hpp"
#include "character/Stats.hpp"
#include "character/Race.hpp"
#include "resources/ResourceManager.hpp"
#include <algorithm>
#include <cstring>
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

  _tile = NULL;
}

Character::Character(const string& name, Race* race, list<CharacterClass*> classes, Stats* initialStats)
  : _name(name)
  , _race(race)
  , _exp(0)
  , _classes(classes)
{
  if( initialStats == NULL ){
    _stats = new Stats();
  }else{
    _stats = initialStats;
  }

  //populate the _stats with the appropriate modifiers
  for(CharacterClass* c : classes){
    _stats->addModifier(c->getModifier());
  }
  _stats->addModifier(_race->getModifier());

  //fill the hp and mp to max
  fillHP();
  fillMP();

  _tile = NULL;
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

int Character::getExp() const{
  return _exp;
}

const string& Character::getName() const{
  return _name;
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

void Character::setHP(int amount){
  _hp = min(amount, _stats->getStat(Stats::MAX_HP));
}

void Character::setMP(int amount){
  _mp = min(amount, _stats->getStat(Stats::MAX_MP));
}

void Character::setExp(int amount){
  _exp = amount;
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

void Character::setTile(Tile* tile){
  _tile = tile;
}

Tile* Character::getTile(){
  return _tile;
}

Stats* Character::getStats(){
  return _stats;
}

Race* Character::getRace(){
  return _race;
}

const list<CharacterClass*>& Character::getClasses(){
  return _classes;
}

void Character::addClass(CharacterClass* cclass){
  _classes.push_back(cclass);
}

DEF_XML_RESOURCE_LOAD(Character){
  if( strcmp(node->name(),"character") != 0 )
    raise(MalformedResourceException,path,string("Expected 'character' node but found '")+node->name()+"'.");

  //value loading loop
  string name="";
  int hp=-1;
  int mp=-1;
  int exp=-1;
  Stats* stats = NULL;
  Race* race = NULL;
  list<CharacterClass*> classes;

  for(XmlNode* child = node->first_node(); child; child = child->next_sibling()){
    if( strcmp(child->name(),"name") == 0 ){
      name = child->value();
    }else if( strcmp(child->name(),"hp") == 0 ){
      hp = atoi(child->value());
    }else if( strcmp(child->name(),"mp") == 0 ){
      mp = atoi(child->value());
    }else if( strcmp(child->name(),"exp") == 0 ){
      exp = atoi(child->value());
    }else if( strcmp(child->name(),"stats") == 0 ){
      stats = XmlResource::load<Stats>(path,child);
    }else if( strcmp(child->name(),"race") == 0 ){
      race = manager->loadResource<Race>(Path(child->value()));
    }else if( strcmp(child->name(),"class") == 0 ){
      CharacterClass* c = manager->loadResource<CharacterClass>(Path(child->value())); 
      classes.push_back( c );

      //set the level of the class if it's specified
      for(XmlAttribute* attr = child->first_attribute(); attr; attr=attr->next_attribute()){
        if( strcmp(attr->name(),"level")==0 ){
          c->setLevel(atoi(attr->value()));
        }
      }
    }
  }

  //sanity checks
  if( name=="" )
    raise(MalformedResourceException,path,"No name supplied in character definition.");
  if( race==NULL )
    raise(MalformedResourceException,path,"No race specified for character.");
  if( classes.size() == 0 )
    raise(MalformedResourceException,path,"No classes supplied for character.");
  if( stats==NULL )
    raise(MalformedResourceException,path,"No stats supplied for character.");
  if( hp<0 )
    raise(MalformedResourceException,path,"No HP supplied for character.");
  if( mp<0 )
    raise(MalformedResourceException,path,"No MP supplied for character.");
  if( exp<0 )
    raise(MalformedResourceException,path,"No experience supplied for character.");

  Character* c = new Character(name, race, classes, stats);
  c->setHP(hp);
  c->setMP(mp);
  c->setExp(exp);

  return c;
}

