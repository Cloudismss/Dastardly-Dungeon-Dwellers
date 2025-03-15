#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "CharacterList.h"
#include "Inventory.h"

using std::string;

class Player
{
private:
  // Progression Variables
  int rooms = 0;

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
  int attack(int battleSelection, const string &enemyName, double enemyVulnerability);

public:
  // Progression Accessors
  int getRoomCount() const { return rooms; }

  // Inventory Accessors
  int getGold() const { return inventory->getGold(); }
  int getPotions() const { return inventory->getPotions(); }
  int getArmor() const { return inventory->getArmor(); }
  int getKeys() const { return inventory->getKeys(); }

  // Progression Mutators
  void roomCleared() { ++rooms; }

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

#endif // PLAYER_H
