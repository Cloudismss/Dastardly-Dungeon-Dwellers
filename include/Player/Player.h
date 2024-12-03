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
  int rooms = 0, progression = 0;

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
  int attack(const string &battleMenuSelection, const string &enemyName, double enemyVulnerability);

public:
  // Progression Accessors
  int getRoomCount() { return rooms; }
  int getProgression() { return progression; }

  // Inventory Accessors
  int getGold() { return inventory->getGold(); }
  int getPotions() { return inventory->getPotions(); }
  int getArmor() { return inventory->getArmor(); }
  int getKeys() { return inventory->getKeys(); }

  // Progression Mutators
  void roomCleared() { ++rooms; }
  void progress() { ++progression; }

  // Inventory Mutators
  void addGold(int goldAdjust) { inventory->addGold(goldAdjust); }
  void addPotions(int potionAdjust = 1) { inventory->addPotions(potionAdjust); }
  void addArmor(int armorAdjust = 1) { inventory->addArmor(armorAdjust); }
  void addKeys(int keyAdjust = 1) { inventory->addKeys(keyAdjust); }

  void removeGold(int goldAdjust) { inventory->removeGold(goldAdjust); }
  void removePotions(int potionAdjust = 1) { inventory->removePotions(potionAdjust); }
  void removeArmor(int armorAdjust = 1) { inventory->removeArmor(armorAdjust); }
  void removeKeys(int keysAdjust = 1) { inventory->removeKeys(keysAdjust); }

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
