#include "Inventory.h"

#include "Art.h"
#include "Game.h"

#include "fmt/color.h"

Inventory::Inventory()
{
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
  // TODO: Print inventory display menu
}

void Inventory::addGold(int goldAdjust)
{
  gold += goldAdjust;
  fmt::print(fmt::emphasis::bold | fg(fmt::color::gold), "Gold x{0} added\n", goldAdjust);
}

void Inventory::addPotions(int potionAdjust)
{
  potions += potionAdjust;
  if (potionAdjust == 1)
    fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "Potion added\n");
  else
    fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "Potion x{0} added\n", potionAdjust);
}

void Inventory::addArmor(int armorAdjust)
{
  armor += armorAdjust;
  if (armorAdjust == 1)
    fmt::print(fmt::emphasis::bold | fg(fmt::color::steel_blue), "Armor Plating added\n");
  else
    fmt::print(fmt::emphasis::bold | fg(fmt::color::steel_blue), "Armor Plating x{0} added\n", armorAdjust);
}

void Inventory::addKeys(int keyAdjust)
{
  ++keys;
  art::box::displayMeInABox("GOLDEN KEY Acquired!");
}
