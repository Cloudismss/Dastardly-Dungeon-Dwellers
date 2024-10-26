#ifndef DASTARDLY_DUNGEON_DWELLERS_PLAYER_H
#define DASTARDLY_DUNGEON_DWELLERS_PLAYER_H

#include <string>

#include "Globals.h"

#include "Skills.h"

using std::string;

class Player
{
public:
  // Constructor
  Player();
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

  // Class selector
  void classSelection();

public:
  // Initialize skills
  Skills *skills;
  
  // Mutators
  double attack(Player *player, const double &enemyVulnerability, const string &battleMenuSelection);
  void receive(double healthAdjust) { health -= healthAdjust; }
  void heal();
  void setClass(const string &CLASS_NAME) { className = CLASS_NAME; }

  void addGold(int goldAdjust);
  void addPotion(int potionAdjust);
  void addArmor(int armorAdjust) { armor += armorAdjust; }
  void addKey();

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