#ifndef DASTARDLY_DUNGEON_DWELLERS_PLAYER_H
#define DASTARDLY_DUNGEON_DWELLERS_PLAYER_H

#include <string>

#include "Characters.h"

using std::string;

class Player
{
public:
  // Constructor
  Player();
  ~Player() { delete characters; }

private:
  // Character linked list
  Characters *characters;

  // Inventory Variables
  short unsigned int gold, potions, armor, keys;
  short unsigned int meleeWeapon, magicWeapon, rangedWeapon;

  // Progression Variables
  short unsigned int rooms, progression;

public:
  // Helper Functions
  void heal();
  double attack(const double &enemyVulnerability, const string &battleMenuSelection);

  // Mutators
  void addGold(int goldAdjust);
  void addPotion(int potionAdjust);
  void addArmor(int armorAdjust);
  void addKey();

  void upgradeWeapon(const string &weaponType, const string &upgradeName);

  void removeGold(int goldAdjust) { gold -= goldAdjust; }
  void removePotion(int potionAdjust) { potions -= potionAdjust; }
  void removeArmor(int armorAdjust) { armor -= armorAdjust; }
  void removeKey() { --keys; }

  void roomCleared() { ++rooms; }
  void progress() { ++progression; }

  // Mutators for character stats
  void adjustHealth(double healValue) { characters->adjustHealth(healValue); }
  void useSkill(const string &battleMenuSelection) { characters->current->skills->useSkill(battleMenuSelection, getClassName()); }

  // Accessors for character stats
  double getHealth() { return characters->current->health; }
  string getClassName() { return characters->current->className; }
  double getCritSkill() { return characters->current->skills->getCritSkill(); }
  int getMeleeSkill() { return characters->current->skills->getMeleeSkill(); }
  int getMagicSkill() { return characters->current->skills->getMagicSkill(); }
  int getRangedSkill() { return characters->current->skills->getRangedSkill(); }
  int getSkillTier(const string &battleMenuSelection) { return characters->current->skills->getSkillTier(battleMenuSelection); }
  string getSkillName(const string &battleMenuSelection) { return characters->current->skills->getSkillName(battleMenuSelection); }

  int getGold() { return gold; }
  int getPotions() { return potions; }
  int getArmor() { return armor; }
  int getKeys() { return keys; }

  int getWeaponLevel(const string &weaponType);
  
  int getRoomCount() { return rooms; }
  int getProgression() { return progression; }
};

#endif //DASTARDLY_DUNGEON_DWELLERS_PLAYER_H