#include "Player.h"

#include <iostream>

#include "Art.h"
#include "Globals.h"

#include "fmt/color.h"

using std::cout;

Player::Player()
{
  characters = new Characters;
  gold = 0;
  potions = 3;
  armor = 0;
  keys = 0;
  meleeWeapon = 1;
  magicWeapon = 1;
  rangedWeapon = 1;
  rooms = 0;
  progression = 0;

  // DEBUG Option - Extra potions, gold, keys
  if (debug)
  {
    potions = 100;
    gold = 1000;
    keys = 10;
  }
}

// Pre-condition: called by battleController(), passed result of battleMenu(), skill variables, enemy variables, and characterStats
// Post-condition: returns a damage amount based on all passed variables
double Player::attack(const double &enemyVulnerability, const string &battleMenuSelection)
{
  // Attack Variables
  double attackValue = 0;
  double critChance = BASE_CRIT_CHANCE * getCritSkill();

  if (battleMenuSelection == "Melee")
    attackValue = BASE_MELEE_DAMAGE * getMeleeSkill();
  else if (battleMenuSelection == "Magic")
    attackValue = BASE_MAGIC_DAMAGE * getMagicSkill();
  else if (battleMenuSelection == "Ranged")
    attackValue = BASE_RANGED_DAMAGE * getRangedSkill();

  // Get skill upgrade tier
  short unsigned int skillTier = getSkillTier(battleMenuSelection);

  // Calculate attackValue
  attackValue *= skillTier * getWeaponLevel(battleMenuSelection);

  // Add a small offset to the damage for a touch of variability
  attackValue += skillTier * (-1 + (rand() % 3));

  // Calculate crit
  if (1 + (rand() % 100) <= critChance * 100)
  {
    attackValue *= 2;
    cout << "\tYou landed a ";
    fmt::print(fmt::emphasis::bold | fg(fmt::color::gold), "critical hit");
    cout << "!\n";
  }

  // Calculate vulnerability
  attackValue *= enemyVulnerability;

  // DEBUG OPTION - Max damage
  if (debug)
    attackValue = 1000.0;

  cout << "\t" << getSkillName(battleMenuSelection) << " dealt " << static_cast<int>(attackValue) << " damage\n\n";

  // Increment skill counter and check for upgrade
  useSkill(battleMenuSelection);

  return attackValue;
}

void Player::addGold(int goldAdjust)
{
  gold += goldAdjust;
  fmt::print(fmt::emphasis::bold | fg(fmt::color::gold), "Gold x{0} added\n", goldAdjust);
}

void Player::addPotion(int potionAdjust)
{
  potions += potionAdjust;
  if (potionAdjust == 1)
    fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "Potion added\n");
  else
    fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "Potion x{0} added\n", potionAdjust);
}

void Player::addArmor(int armorAdjust)
{
  armor += armorAdjust;
  if (armorAdjust == 1)
    fmt::print(fmt::emphasis::bold | fg(fmt::color::steel_blue), "Armor Plating added\n");
  else
    fmt::print(fmt::emphasis::bold | fg(fmt::color::steel_blue), "Armor Plating x{0} added\n", armorAdjust);
}

void Player::addKey()
{
  ++keys;
  displayMeInABox("GOLDEN KEY Acquired!");
}

void Player::upgradeWeapon(const string &weaponType, const string &upgradeName)
{
  if (weaponType == "Melee")
    ++meleeWeapon;
  else if (weaponType == "Magic")
    ++magicWeapon;
  else if (weaponType == "Ranged")
    ++rangedWeapon;

  fmt::print(fmt::emphasis::bold, "{0} added\n", upgradeName);
}

int Player::getWeaponLevel(const string &weaponType)
{
  if (weaponType == "Melee")
    return meleeWeapon;
  else if (weaponType == "Magic")
    return magicWeapon;
  else if (weaponType == "Ranged")
    return rangedWeapon;

  // TODO: Implement clean fix for return in all control paths
  return -1;
}

// Pre-condition: called by battleController(), passed potionCount
// Post-condition: returns an amount to heal the player and updates potionCount
void Player::heal()
{
  if (potions > 0)
  {
    // Picks a random number between 10 and 20 to return a heal amount
    double healValue = 10 + (rand() % 11);
    cout << "\tYou used a potion and healed for ";
         fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "{0}", healValue);
    cout << " health\n";
    cout << "\tYou now have ";
         fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "{0}", --potions);
    cout << " potions\n\n";
    adjustHealth(healValue);
  }
  else
    cout << "\tYou don't have any potions!\n";
}