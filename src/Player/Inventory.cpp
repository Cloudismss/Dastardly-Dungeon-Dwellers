#include "Inventory.h"

#include "Game.h"

Inventory::Inventory()
{
  gold = 0;
  potions = 3;
  armor = 0;
  keys = 0;

  // DEBUG Option - Extra potions, gold, keys
  if (Game::getDebug())
  {
    potions = 100;
    gold = 1000;
    keys = 10;
  }
}

void Inventory::display()
{

}
