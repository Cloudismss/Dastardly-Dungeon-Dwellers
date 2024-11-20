#include "Character.h"

#include <iostream>
#include <fstream>

#include <Art.h>
#include "Globals.h"

#include <fmt/color.h>

using std::cout;

Character::Character()
{
  setClassName();
  readSkills();
  generateSkillNames();
  health = maxHealth;
}

string Character::getRandomAvailableCharacter()
{
  // Check set of available characters
  if (availableCharacters.empty())
    return "None";

  // Select random class name
  int classIndex = rand() % availableCharacters.size();
  set<string>::iterator iter = availableCharacters.begin();
  for (int i = 0; i != classIndex; ++i)
    ++iter;

  return *iter;
}

bool Character::getAvailableCharacter(const string &className)
{
  // Check if character is available
  return availableCharacters.count(className);
}

void Character::checkoutCharacter(const string &className)
{
  // Remove character from set
  availableCharacters.erase(availableCharacters.find(className));
}

// Skills based functions
void Character::readSkills()
{
  // Load 'Character Stats.cfg' or create and load 'Character Stats.cfg' with defaults, the player can edit the .cfg file if they want custom stats
  std::ifstream characterStats;
  characterStats.open("Character Stats.cfg");
  if (!characterStats)
  {
    std::ofstream defaultCharacterStats;
    defaultCharacterStats.open("Character Stats.cfg");
    generateSkills(defaultCharacterStats);
    defaultCharacterStats.close();
    characterStats.open("Character Stats.cfg");
    if (!characterStats)
    {
      std::cerr << "\"Character Stats.cfg\" failed to open!\n";
    }
  }

  string classNameChecker = " ";
  
  // Ignore the first two lines (info header and blank line)
  getline(characterStats, classNameChecker);
  getline(characterStats, classNameChecker);
  while (characterStats.good())
  {
    // Read the class name
    getline(characterStats, classNameChecker, ',');
    // Check the class name
    if (classNameChecker == className)
      characterStats >> meleeLevel >> rangedLevel >> magicLevel >> critLevel >> maxHealth;
    // Check the next line if className doesn't match
    else
      getline(characterStats, classNameChecker);
  }

  characterStats.close();
}



// Pre-condition: valid output file open
// Post-condition: writes default character stats to created file "Character Stats.cfg"
void Character::generateSkills(std::ofstream &defaultCharacterStats)
{
  defaultCharacterStats << "Class Name, Melee Skill | Magic Skill | Ranged Skill | Crit Skill | Max Health\n"
                        << "\n"
                        << "Warrior, 3 2 2 1.0 20.0\n"
                        << "Mage, 1 3 1 3.0 25.0\n"
                        << "Archer, 2 2 3 2.0 15.0\n"
                        << "Bard, 1 1 1 9.0 10.0";
}

// Generic Class Accessors
short unsigned int Character::getWeaponLevel(const string &weaponType)
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

// Class Specific Accessors
short unsigned int Character::getSkillUpgradeTier(const string &skillType)
{
  // Add 1 since upgradeTiers start at index 0
  if (skillType == "Melee")
    return meleeUpgradeTier + 1;
  else if (skillType == "Magic")
    return magicUpgradeTier + 1;
  else if (skillType == "Ranged")
    return magicUpgradeTier + 1;

  // TODO: Implement clean fix for return in all control paths
  return -1;
}

short unsigned int Character::getSkillLevel(const string &skillType)
{
  if (skillType == "Melee")
    return meleeLevel;
  else if (skillType == "Magic")
    return magicLevel;
  else if (skillType == "Ranged")
    return rangedLevel;

  // TODO: Implement clean fix for return in all control paths
  return -1;
}

string Character::getSkillName(const string &skillType)
{
  if (skillType == "Melee")
    return skillNames[skillType][meleeUpgradeTier];
  else if (skillType == "Magic")
    return skillNames[skillType][magicUpgradeTier];
  else if (skillType == "Ranged")
    return skillNames[skillType][rangedUpgradeTier];

  // TODO: Implement clean fix for return in all control paths
  return "Error";
}

// Generic Class Mutators
void Character::addXp(int xpAdjust)
{
  cout << className << " gained " << xpAdjust << " xp!\n";

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

  cout << "\n";
}

void Character::addLevel()
{
  cout << className << " is now level " << ++level << "!\n";
  
  // TODO: Make interesting and print, possibly make virtual

  ++meleeLevel;
  ++magicLevel;
  ++rangedLevel;
  ++critLevel;
  maxHealth += 2;
  health += 2;
}

void Character::upgradeWeapon(const string &weaponType, const string &upgradeName)
{
  if (weaponType == "Melee")
    ++meleeWeapon;
  else if (weaponType == "Magic")
    ++magicWeapon;
  else if (weaponType == "Ranged")
    ++rangedWeapon;

  fmt::print(fmt::emphasis::bold, "{0} added\n", upgradeName);
}

// Class Specific Mutators
void Character::useSkill(const string &skillType)
{
  short unsigned int *upgradeCounter = nullptr;

  if (skillType == "Melee")
    upgradeCounter = &meleeCounter;
  else if (skillType == "Magic")
    upgradeCounter = &magicCounter;
  else if (skillType == "Ranged")
    upgradeCounter = &rangedCounter;

  if (*upgradeCounter + 1 == SKILL_UPGRADE || *upgradeCounter + 1 == SKILL_UPGRADE * 2)
    upgradeSkillName(skillType);

  ++(*upgradeCounter);
}

void Character::upgradeSkillName(const string &skillType)
{
  short unsigned int *skillUpgradeTier = nullptr;

  if (skillType == "Melee")
    skillUpgradeTier = &meleeUpgradeTier;
  else if (skillType == "Magic")
    skillUpgradeTier = &magicUpgradeTier;
  else if (skillType == "Ranged")
    skillUpgradeTier = &rangedUpgradeTier;

  const string upgradeMessage = skillNames[skillType][*skillUpgradeTier] + " has been upgraded to " + skillNames[skillType][(*skillUpgradeTier) + 1];
  ++(*skillUpgradeTier);
 
  // Print skill upgrade notification
  displayMeInABox("Congratulations!", upgradeMessage);
}
