#ifndef DASTARDLY_DUNGEON_DWELLERS_INVENTORY_H
#define DASTARDLY_DUNGEON_DWELLERS_INVENTORY_H

class Inventory
{
private:
  // Inventory Variables
  int gold = 0, potions = 3, armor = 0, keys = 0;

public:
  Inventory();

public:
  // Art function
  void display();

public:
  // Inventory Accessors
  int getGold() { return gold; }
  int getPotions() { return potions; }
  int getArmor() { return armor; }
  int getKeys() { return keys; }

  // Inventory Mutators
  void addGold(int goldAdjust);
  void addPotions(int potionAdjust);
  void addArmor(int armorAdjust);
  void addKeys(int keyAdjust);

  void removeGold(int goldAdjust) { gold -= goldAdjust; }
  void removePotions(int potionAdjust) { potions -= potionAdjust; }
  void removeArmor(int armorAdjust) { armor -= armorAdjust; }
  void removeKeys(int keysAdjust) { keys -= keysAdjust; }
};

#endif // DASTARDLY_DUNGEON_DWELLERS_INVENTORY_H
