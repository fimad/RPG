#ifndef _ITEM_HPP_
#define _ITEM_HPP_

#include "game/Die.hpp"
#include "character/Character.hpp"
#include "resources/XmlResource.hpp"

class Modifier;
class Item : public XmlResource{
  public:
    Item(const string& name, const string& description, int sell, int buy, Character::EquipSlot slots=0, const string& damage="d6");
    ~Item();

    //basic getters
    const string& getName();
    const string& getDescription();
    int getSellPrice();
    int getBuyPrice();
    Die* getDamage();
    Character::EquipSlot getEquipSlot();

    bool hasModifier();
    void setModifier(Modifier* modifier);
    Modifier* getModifier();

  private:
    string _name;
    string _description;
    int _sellPrice;
    int _buyPrice;
    Die* _meleeDamage;
    Character::EquipSlot _slots;
    Modifier* _modifier;
};
MAKE_XML_RESOURCE(Item)


#endif

