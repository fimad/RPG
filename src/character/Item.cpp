#include "character/Item.hpp"
#include "character/Modifier.hpp"
#include <cstring>

Item::Item(const string& name, const string& description, int sell, int buy, Character::EquipSlot slots, const string& damage)
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
  return _slots;
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

  string name = "";
  string description = "";
  int sellPrice = 0;
  int buyPrice = 0;
  string meleeDamage = "";
  Character::EquipSlot slots = 0;
  Modifier* modifier = NULL;

  //value setting loop
  for(XmlNode* child = node->first_node(); child; child = child->next_sibling()){
    if( strcmp(child->name(),"name") == 0 )
      name = child->value();
    if( strcmp(child->name(),"description") == 0 )
      description = child->value();
    if( strcmp(child->name(),"sell") == 0 )
      sellPrice = atoi(child->value());
    if( strcmp(child->name(),"buy") == 0 )
      buyPrice = atoi(child->value());
    if( strcmp(child->name(),"damage") == 0 )
      meleeDamage = child->value();
    if( strcmp(child->name(),"equip_slot") == 0 )
      slots = *(XmlResource::load<Character::EquipSlot>(path,child,manager));
    if( strcmp(child->name(),"modifier") == 0 )
      modifier = XmlResource::load<Modifier>(path,child,manager);
  }

  //sanity checks
  if( name == "" )
    raise(MalformedResourceException,path,"Items require a name.");
  if( name == "" )
    raise(MalformedResourceException,path,"Items require a description.");
  if( meleeDamage == "" )
    meleeDamage = "d6";

  Item* item = new Item(name, description, sellPrice, buyPrice, slots, meleeDamage);

  if( modifier != NULL ){
    item->setModifier(modifier);
  }

  return item;
}

