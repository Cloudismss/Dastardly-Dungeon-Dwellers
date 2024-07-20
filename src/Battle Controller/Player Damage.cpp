#include "Player Damage.h"

// Pre-condition: called by battleController(), passed result of battleMenu(), skill variables, enemy variables, and characterStats
// Post-condition: returns a damage amount based on all passed variables
float playerDamage(int battleMenuSelection, string &meleeName, string &magicName, string &rangedName, const string &className, const string &enemyName, bool boss, std::ifstream &characterStats)
{
  // ! TODO: Moved character stats read implementation

  // Counters that are used to move through the tiers of skill milestones
  static int meleeCounter, magicCounter, rangedCounter;

  // Variables to track current skill values
  int *skillCounter = nullptr;
  string skillName = " ";
  int skillUpgradeIndex = 0;

  // Damage Variables
  float critChance = BASE_CRIT_CHANCE * critSkill;
  float damageValue = 0;

  switch (battleMenuSelection)
  {
    // Melee
    case 1:
    {
      skillCounter = &meleeCounter;
      skillName = meleeName;
      skillUpgradeIndex = 0;
      damageValue = BASE_MELEE_DAMAGE * meleeSkill;
      break;
    }
    // Magic
    case 2:
    {
      skillCounter = &magicCounter;
      skillName = magicName;
      skillUpgradeIndex = 1;
      damageValue = BASE_MAGIC_DAMAGE * magicSkill;
      break;
    }
    // Ranged
    case 3:
    {
      skillCounter = &rangedCounter;
      skillName = rangedName;
      skillUpgradeIndex = 2;
      damageValue = BASE_RANGED_DAMAGE * rangedSkill;
      break;
    }
  }

  // Check skill tier for damage calculations
  int skillTier = 0;
  // Level 1
  if (*skillCounter < SKILL_UPGRADE)
  {
    skillTier = 1;
    ++(*skillCounter);
  }
  // Level 2
  else if (*skillCounter >= SKILL_UPGRADE && *skillCounter < SKILL_UPGRADE * 2)
  {
    skillTier = 2;
    ++(*skillCounter);
  }
  // Level 3
  else if (*skillCounter >= SKILL_UPGRADE * 2)
  {
    skillTier = 3;
    ++(*skillCounter);
  }

  // Calculate damageValue
  damageValue *= skillTier * weaponUpgrade(skillUpgradeIndex) * enemyResistance(skillName, enemyName, boss, battleMenuSelection);

  // Add a small offset to the damage for a touch of variability
  damageValue += (-1 + (rand() % 3)) * skillTier;

  // Calculate crit
  if (1 + (rand() % 100) <= critChance * 100)
  {
    damageValue *= 2;
    cout << "\tYou landed a critical hit!\n";
  }

  // DEBUG OPTION - Max damage
  if (debug)
  {
    damageValue = 100;
  }

  cout << "\t" << skillName << " dealt " << static_cast<int>(damageValue) << " damage\n\n";

  // Print skill upgrade notification
  if (*skillCounter == SKILL_UPGRADE || *skillCounter == SKILL_UPGRADE * 2)
  {
    // Upgrade messages for displayMeInABox function
    string congratulationsMessage = "Congratulations!";
    string upgradeMessage = " ";

    // Bools to make sure messages only prints once
    static bool melee2Once = false, melee3Once = false;
    static bool magic2Once = false, magic3Once = false;
    static bool ranged2Once = false, ranged3Once = false;

    if (meleeCounter == SKILL_UPGRADE)
    {
      if (!melee2Once)
      {
        skillNames(meleeName, "Melee", upgradeMessage, className, 2);
        displayMeInABox(congratulationsMessage,upgradeMessage);
        melee2Once = true;
      }
    }
    else if (meleeCounter == SKILL_UPGRADE * 2)
    {
      if (!melee3Once)
      {
        skillNames(meleeName, "Melee", upgradeMessage, className, 3);
        displayMeInABox(congratulationsMessage,upgradeMessage);
        melee3Once = true;
      }
    }

    if (magicCounter == SKILL_UPGRADE)
    {
      if (!magic2Once)
      {
        skillNames(magicName, "Magic", upgradeMessage, className, 2);
        displayMeInABox(congratulationsMessage,upgradeMessage);
        magic2Once = true;
      }
    }
    else if (magicCounter == SKILL_UPGRADE * 2 && !magic3Once)
    {
      if (!magic3Once)
      {
        skillNames(magicName, "Magic", upgradeMessage, className, 3);
        displayMeInABox(congratulationsMessage,upgradeMessage);
        magic3Once = true;
      }
    }

    if (rangedCounter == SKILL_UPGRADE)
    {
      if (!ranged2Once)
      {
        skillNames(rangedName, "Ranged", upgradeMessage, className, 2);
        displayMeInABox(congratulationsMessage,upgradeMessage);
        ranged2Once = true;
      }
    }
    else if (rangedCounter == SKILL_UPGRADE * 2)
    {
      if (!ranged3Once)
      {
        skillNames(rangedName, "Ranged", upgradeMessage, className, 3);
        displayMeInABox(congratulationsMessage, upgradeMessage);
        ranged3Once = true;
      }
    }
  }

  return damageValue;
}