#include "Inventory.h"

#include "Globals.h"

Inventory::Inventory()
{
  gold = 0;
  potions = 3;
  armor = 0;
  keys = 0;

  // DEBUG Option - Extra potions, gold, keys
  if (debug)
  {
    potions = 100;
    gold = 1000;
    keys = 10;
  }
}

void Inventory::display()
{

}
