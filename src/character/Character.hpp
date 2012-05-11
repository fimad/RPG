#ifndef _CHARACTER_HPP_
#define _CHARACTER_HPP_

#include <list>
#include <string>
#include "scripting/EventRaiser.hpp"
#include "resources/XmlResource.hpp"
using namespace std;

/*
TODO:
Requires Maps/Tiles:
  -doMelee/Spell
  -Facing
Requires Items:
  -Weilding/Wearing
-Feats/Actions
 */

class Tile;
class Race;
class Stats;
class CharacterClass;
class Item;
class Character : public XmlResource{
  public:
    //the slots where things can be equipped on a character
    enum {
        HEAD    = 0x0001
      , TORSO   = 0x0002
      , LEGS    = 0x0004
      , FEET    = 0x0008
      , RING_1  = 0x0010
      , RING_2  = 0x0020
      , AMULET  = 0x0040
      , HAND_1  = 0x0080
      , HAND_2  = 0x0100
    };
    typedef short EquipSlot;

    //The character will own the race, classes and stats supplied
    Character(const string& name, Race* race, CharacterClass* startingClass, Stats* initialStats = NULL);
    Character(const string& name, Race* race, list<CharacterClass*> classes, Stats* initialStats = NULL);
    virtual ~Character();
    int getHP() const;
    int getMP() const;
    int getExp() const;
    const string& getName() const;
    void takeDamage(int amount);
    void useMP(int amount);
    void addHP(int amount);
    void addMP(int amount);
    void addExp(int amount);
    void setHP(int amount);
    void setMP(int amount);
    void setExp(int amount);
    void fillHP();
    void fillMP();
    void addClass(CharacterClass* cclass);
    void setTile(Tile* tile);
    Tile* getTile();
    Stats* getStats();
    Race* getRace();
    const list<CharacterClass*>& getClasses();
    virtual void step(double delta);

    //equipping functions
    bool canEquip(Item* item);
    void equip(Item* item);
    void unEquip(Item* item);
    Item* itemForSlot(EquipSlot);
    bool slotIsFreE(EquipSlot);

  private:
    int _hp;
    int _mp;
    int _exp;
    Tile* _tile;
    Race* _race;
    list<Item*> _equipped;
    string _name;
    Stats* _stats;
    list<CharacterClass*> _classes;
};
MAKE_XML_RESOURCE(Character)

#endif

