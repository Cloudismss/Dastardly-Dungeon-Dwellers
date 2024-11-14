#include "Player.h"

#include <iostream>

#include "Art.h"
#include "Game.h"
#include "Globals.h"

#include "fmt/color.h"

using std::cout;

Player::Player()
{
  characters = new Characters;
  inventory = new Inventory;
  rooms = 0;
  progression = 0;
}

// Pre-condition: called by battleController(), passed result of battleMenu(), skill variables, enemy variables, and characterStats
// Post-condition: returns a damage amount based on all passed variables
double Player::attack(const double &enemyVulnerability, const string &battleMenuSelection)
{
  // Attack Variables
  double attackValue;
  if (battleMenuSelection == "Melee")
    attackValue = BASE_MELEE_DAMAGE;
  else if (battleMenuSelection == "Magic")
    attackValue = BASE_MAGIC_DAMAGE;
  else if (battleMenuSelection == "Ranged")
    attackValue = BASE_RANGED_DAMAGE;

  // Add the product of skillLevel and skillUpgrade
  attackValue += characters->getSkillLevel(battleMenuSelection) * characters->getSkillUpgrade(battleMenuSelection);

  // Multiply by weapon level
  attackValue *= characters->getWeaponLevel(battleMenuSelection);

  // Add a small offset to the damage for a touch of variability
  attackValue += characters->getSkillUpgrade(battleMenuSelection) * (-1 + (rand() % 3));

  // Calculate crit
  double critChance = BASE_CRIT_CHANCE * characters->getcritLevel();
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
  if (Game::getDebug())
    attackValue = 1000.0;

  cout << "\t" << characters->getSkillName(battleMenuSelection) << " dealt " << static_cast<int>(attackValue) << " damage\n\n";

  // Increment skill counter and check for upgrade
  characters->useSkill(battleMenuSelection);

  return attackValue;
}

void Player::addGold(int goldAdjust)
{
  inventory->gold += goldAdjust;
  fmt::print(fmt::emphasis::bold | fg(fmt::color::gold), "Gold x{0} added\n", goldAdjust);
}

void Player::addPotions(int potionAdjust)
{
  inventory->potions += potionAdjust;
  if (potionAdjust == 1)
    fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "Potion added\n");
  else
    fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "Potion x{0} added\n", potionAdjust);
}

void Player::addArmor(int armorAdjust)
{
  inventory->armor += armorAdjust;
  if (armorAdjust == 1)
    fmt::print(fmt::emphasis::bold | fg(fmt::color::steel_blue), "Armor Plating added\n");
  else
    fmt::print(fmt::emphasis::bold | fg(fmt::color::steel_blue), "Armor Plating x{0} added\n", armorAdjust);
}

void Player::addKeys(int keyAdjust)
{
  ++inventory->keys;
  displayMeInABox("GOLDEN KEY Acquired!");
}

// Pre-condition: called by battleController(), passed potionCount
// Post-condition: returns an amount to heal the player and updates potionCount
void Player::heal()
{
  if (inventory->potions > 0)
  {
    // Picks a random number between 10 and 20 to return a heal amount
    double healValue = 10 + (rand() % 11);

    // Update heal value to not overheal
    if (healValue + characters->getHealth() > characters->getMaxHealth())
      healValue = characters->getMaxHealth() - characters->getHealth();

    cout << "\tYou used a potion and healed for ";
         fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "{0}", healValue);
    cout << " health\n";
    cout << "\tYou now have ";
         fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "{0}", --inventory->potions);
    cout << " potions\n\n";

    characters->adjustHealth(healValue);
  }
  else
    cout << "\tYou don't have any potions!\n";
}
