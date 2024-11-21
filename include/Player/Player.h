#ifndef DASTARDLY_DUNGEON_DWELLERS_PLAYER_H
#define DASTARDLY_DUNGEON_DWELLERS_PLAYER_H

#include <string>

#include "Character List.h"
#include "Inventory.h"

using std::string;

class Player
{
private:
  // Progression Variables
  short unsigned int rooms = 0, progression = 0;

  // Character Linked List
  CharacterList *characters;

  // Player Inventory
  Inventory *inventory;

public:
  Player();
  ~Player();

public:
  // Helper Functions
  void heal();
  short unsigned int attack(const string &battleMenuSelection, const string &enemyName, double enemyVulnerability);

public:
  // Progression Accessors
  short unsigned int getRoomCount() { return rooms; }
  short unsigned int getProgression() { return progression; }

  // Inventory Accessors
  short unsigned int getGold() { return inventory->getGold(); }
  short unsigned int getPotions() { return inventory->getPotions(); }
  short unsigned int getArmor() { return inventory->getArmor(); }
  short unsigned int getKeys() { return inventory->getKeys(); }

  // Progression Mutators
  void roomCleared() { ++rooms; }
  void progress() { ++progression; }

  // Inventory Mutators
  void addGold(short unsigned int goldAdjust) { inventory->addGold(goldAdjust); }
  void addPotions(short unsigned int potionAdjust = 1) { inventory->addPotions(potionAdjust); }
  void addArmor(short unsigned int armorAdjust = 1) { inventory->addArmor(armorAdjust); }
  void addKeys(short unsigned int keyAdjust = 1) { inventory->addKeys(keyAdjust); }

  void removeGold(short unsigned int goldAdjust) { inventory->removeGold(goldAdjust); }
  void removePotions(short unsigned int potionAdjust = 1) { inventory->removePotions(potionAdjust); }
  void removeArmor(short unsigned int armorAdjust = 1) { inventory->removeArmor(armorAdjust); }
  void removeKeys(short unsigned int keysAdjust = 1) { inventory->removeKeys(keysAdjust); }

  // Character List Accessors
  CharacterList* getCharacter() { return characters; }

  // Character List Mutators
  void addRandomCharacter() { characters->addRandomCharacter(); }
  void addSpecificCharacter(const string &className) { characters->addSpecificCharacter(className); }
  bool removeCurrentCharacter() { return characters->removeCurrentCharacter(); }
  bool removeSpecificCharacter(const string &className) { return characters->removeSpecificCharacter(className); }
  bool cycle(char direction = 'R') { return characters->cycle(direction); }
};

#endif // DASTARDLY_DUNGEON_DWELLERS_PLAYER_H
