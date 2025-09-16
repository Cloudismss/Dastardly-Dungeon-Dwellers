#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "CharacterList.h"
#include "Inventory.h"

class Player
{
public:
  Player();
  ~Player();

public:
  // Helper Functions
  void heal();
  int attack(int skillType, const std::string &enemyName, double enemyVulnerability);

public:
  // Progression Accessors
  int getRoomCount() const { return rooms; }

  // Inventory Accessors
  int getGold() const { return inventory->getGold(); }
  int getPotions() const { return inventory->getPotions(); }
  int getArmor() const { return inventory->getArmor(); }
  int getKeys() const { return inventory->getKeys(); }

  // Character List Accessors
  CharacterList *getCharacter() { return characters; }

public:
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

  // Character List Mutators
  void appendRandomCharacter() { characters->appendRandomCharacter(); }
  void appendCharacter(const std::string &className) { characters->appendCharacter(className); }
  bool removeCurrentCharacter() { return characters->removeCurrentCharacter(); }
  bool removeCharacter(const std::string &className) { return characters->removeCharacter(className); }
  bool cycle(char direction = 'R') { return characters->cycle(direction); }

private:
  int rooms = 0;
  CharacterList *characters;
  Inventory *inventory;
};

#endif // PLAYER_H
