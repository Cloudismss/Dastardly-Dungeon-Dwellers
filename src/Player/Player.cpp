#include "Player.h"

// Pre-condition: called by battleController(), passed result of battleMenu(), skill variables, enemy variables, and characterStats
// Post-condition: returns a damage amount based on all passed variables
double Player::attack(Player *player, Enemy *enemy, const string &battleMenuSelection)
{
  // Attack Variables
  double attackValue = 0;
  double critChance = BASE_CRIT_CHANCE * player->skills->getCritSkill();

  if (battleMenuSelection == "Melee")
    attackValue = BASE_MELEE_DAMAGE * player->skills->getMeleeSkill();
  else if (battleMenuSelection == "Magic")
    attackValue = BASE_MAGIC_DAMAGE * player->skills->getMagicSkill();
  else if (battleMenuSelection == "Ranged")
    attackValue = BASE_RANGED_DAMAGE * player->skills->getRangedSkill();

  // Get skill upgrade tier
  short unsigned int skillTier = player->skills->getSkillTier(battleMenuSelection);

  // Calculate attackValue
  attackValue *= skillTier * player->getWeaponLevel(battleMenuSelection) * enemy->getResistance(battleMenuSelection);

  // Add a small offset to the damage for a touch of variability
  attackValue += skillTier * (-1 + (rand() % 3));

  // Calculate crit
  if (1 + (rand() % 100) <= critChance * 100)
  {
    attackValue *= 2;
    cout << "\tYou landed a critical hit!\n";
  }

  // DEBUG OPTION - Max damage
  if (debug)
    attackValue = 1000.0;

  cout << "\t" << player->skills->getSkillName(battleMenuSelection) << " dealt " << static_cast<int>(attackValue) << " damage\n\n";

  // Increment skill counter and check for upgrade
  player->skills->useSkill(battleMenuSelection, player->getClass());

  return attackValue;
}

void Player::upgradeWeapon(const string &weaponType)
{
  if (weaponType == "Melee")
    ++meleeWeapon;
  else if (weaponType == "Magic")
    ++magicWeapon;
  else if (weaponType == "Ranged")
    ++rangedWeapon;
}

int Player::getWeaponLevel(const string &weaponType)
{
  if (weaponType == "Melee")
    return meleeWeapon;
  else if (weaponType == "Magic")
    return magicWeapon;
  else if (weaponType == "Ranged")
    return rangedWeapon;
}

// Pre-condition: called by battleController(), passed potionCount
// Post-condition: returns an amount to heal the player and updates potionCount
void Player::heal()
{
  if (potions > 0)
  {
    // Picks a random number between 10 and 20 to return a heal amount
    double healValue = 10 + (rand() % 11);
    cout << "\tYou used a potion and healed for " << healValue << " health\n"
         << "\tYou now have " << --potions << " potions.\n\n";
    health += healValue;
  }
  else
    cout << "\tYou don't have any potions!\n";
}