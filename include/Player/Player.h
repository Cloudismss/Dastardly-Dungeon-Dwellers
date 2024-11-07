#ifndef DASTARDLY_DUNGEON_DWELLERS_PLAYER_H
#define DASTARDLY_DUNGEON_DWELLERS_PLAYER_H

#include <string>

#include "Characters.h"

using std::string;

class Player
{
private:
  // Character linked list
  Characters *characters;

  // Inventory Variables
  short unsigned int gold, potions, armor, keys;

  // Progression Variables
  short unsigned int rooms, progression;

public:
  Player();
  ~Player() { delete characters; }

  // Helper Functions
  void heal();
  double attack(const double &enemyVulnerability, const string &battleMenuSelection);

  // Inventory Mutators
  void addGold(int goldAdjust);
  void addPotion(int potionAdjust);
  void addArmor(int armorAdjust);
  void addKey();

  void removeGold(int goldAdjust) { gold -= goldAdjust; }
  void removePotion(int potionAdjust) { potions -= potionAdjust; }
  void removeArmor(int armorAdjust) { armor -= armorAdjust; }
  void removeKey() { --keys; }

  void upgradeWeapon(const string &weaponType, const string &upgradeName);

  // Inventory Accessors
  int getGold() { return gold; }
  int getPotions() { return potions; }
  int getArmor() { return armor; }
  int getKeys() { return keys; }
  
  int getWeaponLevel(const string &weaponType);

  // Progression Mutators
  void roomCleared() { ++rooms; }
  void progress() { ++progression; }

  // Progression Accessors
  int getRoomCount() { return rooms; }
  int getProgression() { return progression; }

  // Character Stat Mutators
  void adjustHealth(double healValue) { characters->adjustHealth(healValue); }
  void useSkill(const string &battleMenuSelection) { characters->current->skills->useSkill(battleMenuSelection, getClassName()); }

  // Character Stat Accessors
  double getHealth() { return characters->current->health; }
  string getClassName() { return characters->current->className; }
  double getCritSkill() { return characters->current->skills->getCritSkill(); }
  int getMeleeSkill() { return characters->current->skills->getMeleeSkill(); }
  int getMagicSkill() { return characters->current->skills->getMagicSkill(); }
  int getRangedSkill() { return characters->current->skills->getRangedSkill(); }
  int getSkillTier(const string &battleMenuSelection) { return characters->current->skills->getSkillTier(battleMenuSelection); }
  string getSkillName(const string &battleMenuSelection) { return characters->current->skills->getSkillName(battleMenuSelection); }
};

#endif //DASTARDLY_DUNGEON_DWELLERS_PLAYER_H
