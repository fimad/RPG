#include "character/Character.hpp"
#include "character/CharacterClass.hpp"
#include "character/ProxyModifier.hpp"
#include "character/Stats.hpp"
#include "character/Race.hpp"
#include "resources/ResourceManager.hpp"
#include "character/Item.hpp"
#include "map/Tile.hpp"
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

//equipping functions
bool Character::canEquip(Item* item){
  return slotIsFree(item->getEquipSlot());
}

void Character::equip(Item* item){
  EquipSlot newSlot;
  if( translateEquipSlot(item->getEquipSlot(),newSlot) && slotIsFree(newSlot) ){
    _equipped.push_back(make_tuple(newSlot,item));
    if( item->hasModifier() ){
      _stats->addModifier(item->getModifier());
    }
  }
}

void Character::unEquip(Item* item){
  for( auto e : _equipped ){
    if( item == get<1>(e) ){
      remove(_equipped.begin(), _equipped.end(), e);
      if( item->hasModifier() ){
        _stats->removeModifier(item->getModifier());
      }
      break;
    }
  }
}

Item* Character::itemForSlot(EquipSlot slot){
  EquipSlot newSlot;
  translateEquipSlot(slot,newSlot,true);

  for( auto e : _equipped ){
    if( newSlot & get<0>(e) > 0 ){
      return get<1>(e);
    }
  }
  return NULL;
}

bool Character::slotIsFree(EquipSlot slot){
  EquipSlot newSlot;
  if( translateEquipSlot(slot,newSlot) ){
    for( auto e : _equipped ){
      if( newSlot & get<0>(e) > 0 ){
        return false;
      }
    }
    return true;
  }
  return false;
}

//this function is ugly as sin and their is probably nicer way to do this
bool Character::translateEquipSlot(EquipSlot in, EquipSlot& out, bool forSearching){
  out = 0 | ( in & ~(ONE_HANDED | TWO_HANDED | RING) ); //out = in minus one_handed two handed or ring
  //now add back in the equivalents
  if( forSearching ){
    if( in & ONE_HANDED || in & TWO_HANDED ) 
      out |= HAND_1 | HAND_2;
    if( in & RING ) 
      out |= RING_1 | RING_2;
    return true;
  }else{
    //find which of the following are currently free
    bool hand_1 = false;
    bool hand_2 = false;
    bool ring_1 = false;
    bool ring_2 = false;
    for( auto e : _equipped ){
      if( HAND_1 & get<0>(e) )
        hand_1 = true;
      if( HAND_2 & get<0>(e) )
        hand_2 = true;
      if( RING_1 & get<0>(e) )
        ring_1 = true;
      if( RING_2 & get<0>(e) )
        ring_2 = true;
    }

    //check for one handed
    if( in & ONE_HANDED ){
      if( hand_1 )
        out |= HAND_1;
      else if( hand_2 )
        out |= HAND_2;
      else
        return false;
    }

    //check for two handed
    if( in & TWO_HANDED ){
      if( hand_1 && hand_2 )
        out |= HAND_1 | HAND_2;
      else
        return false;
    }

    //check for one ring
    if( in & RING ){
      if( ring_1 )
        out |= RING_1;
      else if( ring_2 )
        out |= RING_2;
      else
        return false;
    }

    return true;
  }
}

//inventory
vector<Item*> Character::getInventory(){
  return _inventory;
}

void Character::removeItem(Item* item){
  remove(_inventory.begin(),_inventory.end(),item);
}

void Character::dropItem(Item* item){
  removeItem(item);
  if(_tile){
    _tile->holdItem(item);
  }
}

void Character::holdItem(Item* item){
  _inventory.push_back(item);
}


//this function is _NOT_ thread safe!
DEF_XML_RESOURCE_LOAD(Character::EquipSlot){
  if( strcmp(node->name(),"equip_slot") != 0 )
    raise(MalformedResourceException,path,string("Expected 'equip_slot' node but found '")+node->name()+"'.");

  static Character::EquipSlot value = 0;

  for(XmlNode* child = node->first_node(); child; child = child->next_sibling()){
    if( strcmp(child->name(),"head") == 0 )
      value |= Character::HEAD;
    if( strcmp(child->name(),"torso") == 0 )
      value |= Character::TORSO;
    if( strcmp(child->name(),"legs") == 0 )
      value |= Character::LEGS;
    if( strcmp(child->name(),"feet") == 0 )
      value |= Character::FEET;
    if( strcmp(child->name(),"ring") == 0 )
      value |= Character::RING;
    if( strcmp(child->name(),"one_handed") == 0 )
      value |= Character::ONE_HANDED;
    if( strcmp(child->name(),"two_handed") == 0 )
      value |= Character::TWO_HANDED;
  }

  if( value & Character::ONE_HANDED && value & Character::TWO_HANDED ){
    raise(MalformedResourceException,path,"Cannot have both one_handed and two_handed set for the same slot.")
  }

  return &value;
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
  list<Item*> equipped;
  list<Item*> inventory;

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
    }else if( strcmp(child->name(),"equipped") == 0 ){
      for(XmlNode* item = child->first_node(); item; item = item->next_sibling())
        equipped.push_back( manager->loadResource<Item>(Path(item->value())) );
    }else if( strcmp(child->name(),"inventory") == 0 ){
      for(XmlNode* item = child->first_node(); item; item = item->next_sibling())
        inventory.push_back( manager->loadResource<Item>(Path(item->value())) );
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

  for( Item* i : equipped )
    c->equip(i);
  for( Item* i : inventory )
    c->holdItem(i);

  return c;
}

