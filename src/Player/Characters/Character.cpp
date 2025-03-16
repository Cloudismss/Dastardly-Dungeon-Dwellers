#include "Character.h"

#include <iostream>
#include <fstream>
#include <string>

#include "Globals.h"

#include "BoxArt.h"

#include <fmt/color.h>

Character::Character(const std::string& className, const std::unordered_map<int, std::array<std::string, 3>> skillNames) :
  className(className),
  skillNames(skillNames)
{
  initSkills();
  health = maxHealth;
}

std::string Character::getRandomAvailableCharacter()
{
  // Check set of available characters
  if (availableCharacters.empty())
    return "None";

  // Select random class name
  int classIndex = rand() % availableCharacters.size();
  auto iter = availableCharacters.begin();
  for (int i = 0; i != classIndex; ++i)
    ++iter;

  return *iter;
}

bool Character::getAvailability(const std::string &className)
{
  // Check if character is available
  return availableCharacters.count(className);
}

void Character::checkoutCharacter(const std::string &className)
{
  // Remove character from set
  availableCharacters.erase(availableCharacters.find(className));
}

// Skills based functions
void Character::initSkills()
{
  // Load 'DastardlyDungeonDwellers.cfg' or create and load 'DastardlyDungeonDwellers.cfg' with defaults, the player can edit the .cfg file if they want custom stats
  std::ifstream characterStats;
  characterStats.open("DastardlyDungeonDwellers.cfg");
  if (!characterStats)
  {
    std::ofstream defaultCharacterStats;
    defaultCharacterStats.open("DastardlyDungeonDwellers.cfg");
    generateSkills(defaultCharacterStats);
    defaultCharacterStats.close();
    characterStats.open("DastardlyDungeonDwellers.cfg");
    if (!characterStats)
    {
      std::cerr << "\"DastardlyDungeonDwellers.cfg\" failed to open!\n";
    }
  }

  std::string classNameChecker;
  
  // Ignore the first two lines (info header and blank line)
  getline(characterStats, classNameChecker);
  getline(characterStats, classNameChecker);
  while (characterStats.good())
  {
    // Read the class name
    getline(characterStats, classNameChecker, ',');
    // Check the class name
    if (classNameChecker == className)
    {
      double healthSkill;
      characterStats >> meleeLevel >> magicLevel >> rangedLevel >> critLevel >> healthSkill;
      maxHealth = BASE_PLAYER_HEALTH * healthSkill;
    }
    // Check the next line if className doesn't match
    else
      getline(characterStats, classNameChecker);
  }

  characterStats.close();
}

void Character::generateSkills(std::ofstream &defaultCharacterStats)
{
  defaultCharacterStats << "Class Name, Melee Skill | Magic Skill | Ranged Skill | Crit Skill | Health Skill\n"
                        << "\n"
                        << "Warrior, 20 12 12 1.0 0.9\n"
                        << "Mage, 12 20 14 3.0 0.8\n"
                        << "Archer, 16 12 20 2.0 0.6\n"
                        << "Bard, 15 15 15 9.0 0.4";
}

int Character::getWeaponLevel(int skillType) const
{
  if (skillType == skill::MELEE)
    return meleeWeapon;
  else if (skillType == skill::MAGIC)
    return magicWeapon;
  else if (skillType == skill::RANGED)
    return rangedWeapon;

  // TODO: Implement clean fix for return in all control paths
  return -1;
}

int Character::getSkillUpgradeTier(int skillType) const
{
  // Add 1 since upgradeTiers start at index 0
  if (skillType == skill::MELEE)
    return meleeUpgradeTier + 1;
  else if (skillType == skill::MAGIC)
    return magicUpgradeTier + 1;
  else if (skillType == skill::RANGED)
    return magicUpgradeTier + 1;

  // TODO: Implement clean fix for return in all control paths
  return -1;
}

int Character::getSkillLevel(int skillType) const
{
  if (skillType == skill::MELEE)
    return meleeLevel;
  else if (skillType == skill::MAGIC)
    return magicLevel;
  else if (skillType == skill::RANGED)
    return rangedLevel;

  // TODO: Implement clean fix for return in all control paths
  return -1;
}

std::string Character::getSkillName(int skillType)
{
  if (skillType == skill::MELEE)
    return skillNames.at(skillType)[meleeUpgradeTier];
  else if (skillType == skill::MAGIC)
    return skillNames.at(skillType)[magicUpgradeTier];
  else if (skillType == skill::RANGED)
    return skillNames.at(skillType)[rangedUpgradeTier];

  // TODO: Implement clean fix for return in all control paths
  return "Error";
}

void Character::addXp(int xpAdjust)
{
  std::cout << className << " gained " << xpAdjust << " xp!\n";

  // XP amount exceeds a full level
  while(xpAdjust >= xpRequiredPerLevel)
  {
    addLevel();
    xpAdjust -= xpRequiredPerLevel;
  }

  // Player levels up with adjustment
  if (xp + xpAdjust >= xpRequiredPerLevel)
  {
    int difference = xpRequiredPerLevel - xp;
    xpAdjust -= difference;
    addLevel();
    xp = 0;
  }

  xp += xpAdjust;

  std::cout << "\n";
}

void Character::addLevel()
{
  std::cout << className << " is now level " << ++level << "!\n";
  
  // TODO: Make interesting and print, possibly make virtual

  meleeLevel *= 1.1;
  magicLevel *= 1.1;
  rangedLevel *= 1.1;
  health += maxHealth * 0.1;
  maxHealth *= 1.1;
}

void Character::upgradeWeapon(int skillType, const std::string &upgradeName)
{
  if (skillType == skill::MELEE)
    ++meleeWeapon;
  else if (skillType == skill::MAGIC)
    ++magicWeapon;
  else if (skillType == skill::RANGED)
    ++rangedWeapon;

  fmt::print(fmt::emphasis::bold, "{0} added\n", upgradeName);
}

void Character::useSkill(int skillType)
{
  int *upgradeCounter = nullptr;

  if (skillType == skill::MELEE)
    upgradeCounter = &meleeCounter;
  else if (skillType == skill::MAGIC)
    upgradeCounter = &magicCounter;
  else if (skillType == skill::RANGED)
    upgradeCounter = &rangedCounter;

  if (*upgradeCounter + 1 == SKILL_UPGRADE || *upgradeCounter + 1 == SKILL_UPGRADE * 2)
    upgradeSkillName(skillType);

  ++(*upgradeCounter);
}

void Character::upgradeSkillName(int skillType)
{
  int *skillUpgradeTier = nullptr;

  if (skillType == skill::MELEE)
    skillUpgradeTier = &meleeUpgradeTier;
  else if (skillType == skill::MAGIC)
    skillUpgradeTier = &magicUpgradeTier;
  else if (skillType == skill::RANGED)
    skillUpgradeTier = &rangedUpgradeTier;

  const std::string upgradeMessage = skillNames.at(skillType)[*skillUpgradeTier] + " has been upgraded to " + skillNames.at(skillType)[(*skillUpgradeTier)++];
 
  // Print skill upgrade notification
  art::box::displayMeInABox("Congratulations!", upgradeMessage);
}
