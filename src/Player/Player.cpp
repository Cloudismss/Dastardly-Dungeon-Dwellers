#include "Player.h"

#include <iostream>
#include <string>

#include "Globals.h"

#include "Game.h"

#include "fmt/color.h"

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

int Player::attack(int skillType, const std::string &enemyName, double enemyVulnerability)
{
  // DEBUG OPTION - Max damage
  if (Game::getDebug())
    return 1000;

  int attackValue;
  double missChance;

  switch (skillType)
  {
    case skill::MELEE:
      attackValue = BASE_PLAYER_MELEE_DAMAGE;
      missChance = BASE_MELEE_MISS_CHANCE;
      break;
    case skill::MAGIC:
      attackValue = BASE_PLAYER_MAGIC_DAMAGE;
      missChance = BASE_MAGIC_MISS_CHANCE;
      break;
    case skill::RANGED:
      attackValue = BASE_PLAYER_RANGED_DAMAGE;
      missChance = BASE_RANGED_MISS_CHANCE;
      break;
  }

  if (1 + (rand() % 100) <= missChance * 100)
  {
    std::cout << "\tYour attack missed!\n\n";
    return 0;
  }

  // Multiply by weapon level damage boost
  int weaponLevel = characters->getWeaponLevel(skillType);
  int weaponBoost = 1;
  for (int i = 1; i < weaponLevel; ++i)
    weaponBoost += 0.30; // 30% weapon damage boost per weapon level
  attackValue *= weaponBoost;

  // Multiply by skillUpgrade
  int skillUpgradeTier = characters->getSkillUpgradeTier(skillType);
  int skillTierBoost = 0;
  for (int i = 1; i < skillUpgradeTier; ++i)
    skillTierBoost += 10;
  attackValue += skillTierBoost;

  // Flat skillLevel boost
  int skillLevel = characters->getSkillLevel(skillType);
  attackValue += skillLevel;

  // Add a small offset to the damage for a touch of variability
  int attackLow = -0.1 * attackValue;
  int attackHigh = 0.1 * attackValue;
  attackValue += (attackLow + (rand() % ((attackHigh + 1) - attackLow)));

  // Calculate crit
  double critChance = BASE_CRIT_CHANCE * characters->getCritLevel();
  if (1 + (rand() % 100) <= critChance * 100)
  {
    attackValue *= 1.2;
    std::cout << "\tYou landed a ";
    fmt::print(fmt::emphasis::bold | fg(fmt::color::gold), "critical hit");
    std::cout << "!\n";
  }

  // Calculate vulnerability
  const std::string skillName = characters->getSkillName(skillType);
  if (enemyVulnerability < 1.0)
  {
    std::cout << "\t" << skillName << " is ";
    fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "not very effective");
    std::cout << " against " << enemyName << "!\n";
  }
  else if (enemyVulnerability > 1.5)
  {
    std::cout << "\t" << skillName << " is ";
    fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "super effective");
    std::cout << " against " << enemyName << "!\n";
  }
  attackValue *= enemyVulnerability;

  std::cout << "\t" << characters->getSkillName(skillType) << " dealt " << attackValue << " damage\n\n";

  // Increment skill counter and check for upgrade
  characters->useSkill(skillType);

  return attackValue;
}

void Player::heal()
{
  if (getPotions() > 0)
  {
    // Remove a potion
    removePotions();

    int thirty = (0.3 * characters->getMaxHealth());
    int fifty = (0.5 * characters->getMaxHealth());

    // Picks a random number between 30% and 50% of maxHealth to return a heal amount
    int healValue = thirty + (rand() % (fifty + 1));

    // Update heal value to not overheal
    if (healValue + characters->getHealth() > characters->getMaxHealth())
      healValue = characters->getMaxHealth() - characters->getHealth();

    std::cout << "\tYou used a potion and healed for ";
    fmt::print(fmt::emphasis::bold | fg(fmt::color::green), "{0}", healValue);
    std::cout << " health\n";
    std::cout << "\tYou now have ";
    fmt::print(fmt::emphasis::bold | fg(fmt::color::red), "{0}", getPotions());
    std::cout << " potions\n\n";

    characters->adjustHealth(healValue);
  }
  else
    std::cout << "\tYou don't have any potions!\n";
}
