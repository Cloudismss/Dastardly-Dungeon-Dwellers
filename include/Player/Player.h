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

  // Inventory Accessors
  int getGold() { return inventory->gold; }
  int getPotions() { return inventory->potions; }
  int getArmor() { return inventory->armor; }
  int getKeys() { return inventory->keys; }

  // Inventory Mutators
  void addGold(int goldAdjust);
  void addPotions(int potionAdjust = 1);
  void addArmor(int armorAdjust = 1);
  void addKeys(int keyAdjust = 1);

  void removeGold(int goldAdjust) { inventory->gold -= goldAdjust; }
  void removePotions(int potionAdjust) { inventory->potions -= potionAdjust; }
  void removeArmor(int armorAdjust) { inventory->armor -= armorAdjust; }
  void removeKeys() { --inventory->keys; }

  // Progression Accessors
  int getRoomCount() { return rooms; }
  int getProgression() { return progression; }

  // Progression Mutators
  void roomCleared() { ++rooms; }
  void progress() { ++progression; }

  // Characters Accessors
  string getClassName() { return characters->getClassName(); }
  double getMaxHealth() { return characters->getMaxHealth(); }
  double getHealth() { return characters->getHealth(); }
  string getSkillName(const string &skillType) { return characters->getSkillName(skillType); }

  // Characters Mutators
  void addCharacter() { characters->addCharacter(); }
  bool cycle(char direction) { return characters->cycle(direction); }
  void adjustHealth(double healthAdjust) { characters->adjustHealth(healthAdjust); }
  void upgradeWeapon(const string &weaponType, const string &upgradeName) { characters->upgradeWeapon(weaponType, upgradeName); }
  void addXp(int xpAdjust) { characters->addXp(xpAdjust); }
};

#endif // DASTARDLY_DUNGEON_DWELLERS_PLAYER_H
