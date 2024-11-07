#ifndef DASTARDLY_DUNGEON_DWELLERS_INVENTORY_H
#define DASTARDLY_DUNGEON_DWELLERS_INVENTORY_H

class Inventory
{
private:
  friend class Player;

  // Inventory Variables
  short unsigned int gold, potions, armor, keys;

public:
  Inventory();

  void display();
};

#endif // DASTARDLY_DUNGEON_DWELLERS_INVENTORY_H
