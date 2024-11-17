#include "Skills.h"

#include <iostream>
#include <fstream>

#include "Art.h"

Skills::Skills(const string &className)
{
  readSkills(className);
  generateSkillNames(className);
}

void Skills::readSkills(const string &className)
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
void Skills::generateSkills(std::ofstream &defaultCharacterStats)
{
  defaultCharacterStats << "Class Name, Melee Skill | Magic Skill | Ranged Skill | Crit Skill | Max Health\n"
                        << "\n"
                        << "Warrior, 3 2 2 1.0 20.0\n"
                        << "Mage, 1 3 1 3.0 25.0\n"
                        << "Archer, 2 2 3 2.0 15.0\n"
                        << "Bard, 1 1 1 9.0 10.0";
}

void Skills::generateSkillNames(const string &className)
{
  // Number of skill levels per skill
  const short unsigned int SIZE = 3;

  const string *meleeName, *magicName, *rangedName;

  if (className == "Warrior")
  {
    // Warrior Skill Names
    const string warriorMelee[] = {"Slash", "Cleave", "Behemoth Strike"};
    const string warriorMagic[] = {"Shield Charge", "Vortex Slam", "Arcane Lunge"};
    const string warriorRanged[] = {"Rock Throw", "Shield Throw", "Javelin Toss"};

    meleeName = warriorMelee;
    magicName = warriorMagic;
    rangedName = warriorRanged;
  }
  else if (className == "Mage")
  {
    // Mage Skill Names
    const string mageMelee[] = {"Bonk", "Whack", "Astral Thump"};
    const string mageMagic[] = {"Frost Blast", "Arctic Veil", "Flash Freeze"};
    const string mageRanged[] = {"Zap", "Thunderbolt", "Thunderstorm"};

    meleeName = mageMelee;
    magicName = mageMagic;
    rangedName = mageRanged;
  }
  else if (className == "Archer")
  {
    // Archer Skill Names
    const string archerMelee[] = {"Slice", "Sever", "Blade Dance"};
    const string archerMagic[] = {"Poison Bomb", "Intoxicate", "Pestilence"};
    const string archerRanged[] = {"Pierce", "Perforate", "Serpent Shot"};

    meleeName = archerMelee;
    magicName = archerMagic;
    rangedName = archerRanged;
  }
  else if (className == "Bard")
  {
    // Bard Skill Names
    const string bardMelee[] = {"Slap", "Snuggle", "Strum"};
    const string bardMagic[] = {"Beg", "Sing", "Serenade"};
    const string bardRanged[] = {"Waft", "Whistle", "Seduce"};

    meleeName = bardMelee;
    magicName = bardMagic;
    rangedName = bardRanged;
  }

  for (int i = 0; i != SIZE; ++i)
  {
    skillNames["Melee"][i] = meleeName[i];
    skillNames["Magic"][i] = magicName[i];
    skillNames["Ranged"][i] = rangedName[i];
  }
}
