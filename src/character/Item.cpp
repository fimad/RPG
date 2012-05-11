#include "Item.hpp"

Item::Item(const string& name, const string& description, int sell, int buy, Character::EquipSlots slots=0, const string& damage="d6")
  : _name(name)
  , _description(description)
  , _sellPrice(sell)
  , _buyPrice(buy)
  , _slots(slots)
{
  _meleeDamage = Die::parse(damage);
  _modifier = 0;
}

Item::~Item(){
  if( _modifier )
    delete _modifier;
}


//basic getters
const string& Item::getName(){
  return _name;
}

const string& Item::getDescription(){
  return _description;
}

int Item::getSellPrice(){
  return _sellPrice;
}

int Item::getBuyPrice(){
  return _buyPrice;
}

Die* Item::getDamage(){
  return _meleeDamage;
}

Character::EquipSlot Item::getEquipSlot(){
  return _slot;
}


bool Item::hasModifier(){
  return _modifier!=0;
}

void Item::setModifier(Modifier* modifier){
  if( _modifier )
    delete _modifier;
  _modifier = modifier;
}

Modifier* Item::getModifier(){
  return _modifier;
}

DEF_XML_RESOURCE_LOAD(Item){
  if( strcmp(node->name(),"item") != 0 )
    raise(MalformedResourceException,path,string("Expected 'item' node but found '")+node->name()+"'.");
  return NULL;
}

