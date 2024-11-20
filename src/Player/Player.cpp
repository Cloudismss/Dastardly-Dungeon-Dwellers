#include "Player.h"

#include <iostream>

#include "Art.h"
#include "Game.h"
#include "Globals.h"

#include "fmt/color.h"

using std::cout;

Player::Player()
{
  characters = new CharacterList;
  inventory = new Inventory;
}

Player::~Player()
{
  delete characters;
  delete inventory;
}

// Pre-condition: called by battleController(), passed result of battleMenu(), skill variables, enemy variables, and characterStats
// Post-condition: returns a damage amount based on all passed variables
double Player::attack(const double &enemyVulnerability, const string &battleMenuSelection)
{
  // DEBUG OPTION - Max damage
  if (Game::getDebug())
    return 1000.0;

  // Attack Variables
  double attackValue;
  if (battleMenuSelection == "Melee")
    attackValue = BASE_MELEE_DAMAGE;
  else if (battleMenuSelection == "Magic")
    attackValue = BASE_MAGIC_DAMAGE;
  else if (battleMenuSelection == "Ranged")
    attackValue = BASE_RANGED_DAMAGE;

  // Add the product of skillLevel and skillUpgrade
  attackValue += characters->getSkillLevel(battleMenuSelection) * characters->getSkillUpgradeTier(battleMenuSelection);

  // Multiply by weapon level
  attackValue *= characters->getWeaponLevel(battleMenuSelection);

  // Add a small offset to the damage for a touch of variability
  attackValue += characters->getSkillUpgradeTier(battleMenuSelection) * (-1 + (rand() % 3));

  // Calculate crit
  double critChance = BASE_CRIT_CHANCE * characters->getCritLevel();
  if (1 + (rand() % 100) <= critChance * 100)
  {
    attackValue *= 2;
    cout << "\tYou landed a ";
    fmt::print(fmt::emphasis::bold | fg(fmt::color::gold), "critical hit");
    cout << "!\n";
  }

  // Calculate vulnerability
  attackValue *= enemyVulnerability;

  // TODO: Temp floor until custom GUI healthbar is implemented
  attackValue = floor(attackValue);

  cout << "\t" << characters->getSkillName(battleMenuSelection) << " dealt " << attackValue << " damage\n\n";

  // Increment skill counter and check for upgrade
  characters->useSkill(battleMenuSelection);

  return attackValue;
}

// Pre-condition: called by battleController(), passed potionCount
// Post-condition: returns an amount to heal the player and updates potionCount
void Player::heal()
{
  if (getPotions() > 0)
  {
    // Remove a potion
    removePotions();
    
    // Picks a random number between 10 and 20 to return a heal amount
    double healValue = 10 + (rand() % 11);

    // Update heal value to not overheal
    if (healValue + characters->getHealth() > characters->getMaxHealth())
      healValue = characters->getMaxHealth() - characters->getHealth();

    // TODO: Temp floor until custom GUI healthbar is implemented
    healValue = floor(healValue);

    cout << "\tYou used a potion and healed for ";
         fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "{0}", healValue);
    cout << " health\n";
    cout << "\tYou now have ";
         fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "{0}", getPotions());
    cout << " potions\n\n";

    characters->adjustHealth(healValue);
  }
  else
    cout << "\tYou don't have any potions!\n";
}
