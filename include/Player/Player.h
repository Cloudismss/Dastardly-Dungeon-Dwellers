#ifndef DASTARDLY_DUNGEON_DWELLERS_PLAYER_H
#define DASTARDLY_DUNGEON_DWELLERS_PLAYER_H

#include <string>

#include "Characters.h"
#include "Inventory.h"

using std::string;

class Player
{
private:
  // Character Linked List
  Characters *characters;

  // Player Inventory
  Inventory *inventory;

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

  void removeGold(int goldAdjust) { inventory->gold -= goldAdjust; }
  void removePotion(int potionAdjust) { inventory->potions -= potionAdjust; }
  void removeArmor(int armorAdjust) { inventory->armor -= armorAdjust; }
  void removeKey() { --inventory->keys; }

  void upgradeWeapon(const string &weaponType, const string &upgradeName);

  // Inventory Accessors
  int getGold() { return inventory->gold; }
  int getPotions() { return inventory->potions; }
  int getArmor() { return inventory->armor; }
  int getKeys() { return inventory->keys; }
  
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
  double getMaxHealth() { return characters->current->maxHealth; }
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
