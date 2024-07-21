#ifndef DASTARDLY_DUNGEON_DWELLERS_PLAYER_H
#define DASTARDLY_DUNGEON_DWELLERS_PLAYER_H

#include <string>

#include "Globals.h"

#include "Enemy.h"

using std::string;

class Player
{
public:
  // Constructor
  Player()
  {
    health = 20.0;
    className = " ";
    gold = 0;
    potions = 3;
    armor = 0;
    keys = 0;
    meleeWeapon = 0;
    magicWeapon = 0;
    rangedWeapon = 0;
    rooms = 0;
    progression = 0;

    // DEBUG Option - Extra potions, gold, keys
    if (debug)
    {
      health = 100.0;
      potions = 100;
      gold = 1000;
      keys = 10;
    }
  }
  ~Player() { delete skills; }

private:
  // Player Information
  double health;
  string className;

  // Inventory Variables
  short unsigned int gold, potions, armor, keys;
  short unsigned int meleeWeapon, magicWeapon, rangedWeapon;

  // Progression Variables
  short unsigned int rooms, progression;

public:
  // Initialize skills
  Skills *skills = new Skills(className);
  
  // Mutators
  double attack(Player *player, Enemy *enemy, const string &battleMenuSelection);
  void receive(double healthAdjust) { health -= healthAdjust; }
  void heal();
  void setClass(const string &CLASS_NAME) { className = CLASS_NAME; }

  void addGold(int goldAdjust) { gold += goldAdjust; }
  void addPotion(int potionAdjust) { potions += potionAdjust; }
  void addArmor(int armorAdjust) { armor += armorAdjust; }
  void addKey() { ++keys; }

  void upgradeWeapon(const string &weaponType);

  void removeGold(int goldAdjust) { gold -= goldAdjust; }
  void removePotion(int potionAdjust) { potions -= potionAdjust; }
  void removeArmor(int armorAdjust) { armor -= armorAdjust; }
  void removeKey() { --keys; }

  void roomCleared() { ++rooms; }
  void progress() { ++progression; }

  // Accessors
  double getHealth() { return health; }
  string getClass() { return className; }

  int getGold() { return gold; }
  int getPotions() { return potions; }
  int getArmor() { return armor; }
  int getKeys() { return keys; }

  int getWeaponLevel(const string &weaponType);
  
  int getRoomCount() { return rooms; }
  int getProgression() { return progression; }
};

#endif //DASTARDLY_DUNGEON_DWELLERS_PLAYER_H