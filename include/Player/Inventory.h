#ifndef INVENTORY_H
#define INVENTORY_H

class Inventory
{
public:
  Inventory();

public:
  // Art function
  void display() const;

public:
  // Inventory Accessors
  int getGold() const { return gold; }
  int getPotions() const { return potions; }
  int getArmor() const { return armor; }
  int getKeys() const { return keys; }

public:
  // Inventory Mutators
  void addGold(int goldAdjust);
  void addPotions(int potionAdjust);
  void addArmor(int armorAdjust);
  void addKeys(int keyAdjust);

  void removeGold(int goldAdjust) { gold -= goldAdjust; }
  void removePotions(int potionAdjust) { potions -= potionAdjust; }
  void removeArmor(int armorAdjust) { armor -= armorAdjust; }
  void removeKeys(int keysAdjust) { keys -= keysAdjust; }

private:
  int gold = 0;
  int potions = 3;
  int armor = 0;
  int keys = 0;
};

#endif // INVENTORY_H
