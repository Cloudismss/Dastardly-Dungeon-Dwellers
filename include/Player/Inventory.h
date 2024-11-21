#ifndef DASTARDLY_DUNGEON_DWELLERS_INVENTORY_H
#define DASTARDLY_DUNGEON_DWELLERS_INVENTORY_H

class Inventory
{
private:
  // Inventory Variables
  short unsigned int gold = 0, potions = 3, armor = 0, keys = 0;

public:
  Inventory();

public:
  // Art function
  void display();

public:
  // Inventory Accessors
  short unsigned int getGold() { return gold; }
  short unsigned int getPotions() { return potions; }
  short unsigned int getArmor() { return armor; }
  short unsigned int getKeys() { return keys; }

  // Inventory Mutators
  void addGold(short unsigned int goldAdjust);
  void addPotions(short unsigned int potionAdjust);
  void addArmor(short unsigned int armorAdjust);
  void addKeys(short unsigned int keyAdjust);

  void removeGold(short unsigned int goldAdjust) { gold -= goldAdjust; }
  void removePotions(short unsigned int potionAdjust) { potions -= potionAdjust; }
  void removeArmor(short unsigned int armorAdjust) { armor -= armorAdjust; }
  void removeKeys(short unsigned int keysAdjust) { keys -= keysAdjust; }
};

#endif // DASTARDLY_DUNGEON_DWELLERS_INVENTORY_H
