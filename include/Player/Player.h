#ifndef DASTARDLY_DUNGEON_DWELLERS_PLAYER_H
#define DASTARDLY_DUNGEON_DWELLERS_PLAYER_H

#include <iostream>

using std::cout;

class Player
{
private:
  double health = 20.0;
  // Inventory Variables
  short unsigned int gold = 0;
  short unsigned int potions = 3;
  short unsigned int armor = 0;
  short unsigned int keys = 0;

  // Progression Variables
  short unsigned int rooms = 0;
  short unsigned int progression = 0;

public:
  // Mutators
  void hurt(double healthAdjust) { health -= healthAdjust; }
  void heal(double healthAdjust) { health += healthAdjust; }

  void addGold(int goldAdjust) { gold += goldAdjust; }
  void addPotion(int potionAdjust) { potions += potionAdjust; }
  void addArmor(int armorAdjust) { armor += armorAdjust; }
  void addKey() { ++keys; }

  void removeGold(int goldAdjust) { gold -= goldAdjust; }
  void removePotion(int potionAdjust) { potions -= potionAdjust; }
  void removeArmor(int armorAdjust) { armor -= armorAdjust; }
  void removeKey() { --keys; }

  void roomCleared() { ++rooms; }
  void progress() { ++progression; }

  // Accessors
  double getHealth() { return health; }
  int getGold() { return gold; }
  int getPotions() { return potions; }
  int getArmor() { return armor; }
  int getKeys() { return keys; }
  int getRoomCount() { return rooms; }
  int getProgression() { return progression; }

};

int heal(int &potionCount);

#endif //DASTARDLY_DUNGEON_DWELLERS_PLAYER_H