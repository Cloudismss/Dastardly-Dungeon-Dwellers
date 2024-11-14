#include "Skills.h"

#include <iostream>
#include <fstream>

#include "Art.h"

Skills::Skills(const string &className)
{
  meleeName = " ";
  magicName = " ";
  rangedName = " ";
  meleeCounter = 0;
  magicCounter = 0;
  rangedCounter = 0;
  meleeLevel = 0;
  magicLevel = 0;
  rangedLevel = 0;
  critLevel = 1.0;
  initSkillNames(className);
  readSkills(className);
}

void Skills::readSkills(const string &className)
{
  // Load Character Stats.txt or create and load Character Stats.txt with defaults, the player can edit the .txt file if they want custom stats
  std::ifstream characterStats;
  characterStats.open("Character Stats.txt");
  if (!characterStats)
  {
    std::ofstream defaultCharacterStats;
    defaultCharacterStats.open("Character Stats.txt");
    generateSkills(defaultCharacterStats);
    defaultCharacterStats.close();
    characterStats.open("Character Stats.txt");
    if (!characterStats)
    {
      std::cerr << "Character Stats.txt failed to open!\n";
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
      characterStats >> meleeLevel >> rangedLevel >> magicLevel >> critLevel;
    // Check the next line if className doesn't match
    else
      getline(characterStats, classNameChecker);
  }

  characterStats.close();
}

// Pre-condition: valid output file open
// Post-condition: writes default character stats to created file "Character Stats.txt"
void Skills::generateSkills(std::ofstream &defaultCharacterStats)
{
  defaultCharacterStats << "Class Name, Melee Skill | Magic Skill | Ranged Skill | Crit Skill\n"
                        << "\n"
                        << "Warrior, 3 2 2 1.0\n"
                        << "Mage, 1 3 2 3.0\n"
                        << "Archer, 2 2 3 1.0\n"
                        << "Bard, 1 1 1 9.0";
}

void Skills::initSkillNames(const string &className)
{
  // Warrior Skills
  if (className == "Warrior")
  {
    meleeName = "Slash";
    magicName = "Shield Charge";
    rangedName = "Rock Throw";
  }

  // Mage Skills
  else if (className == "Mage")
  {
    meleeName = "Bonk";
    magicName = "Frost Blast";
    rangedName = "Zap";
  }

  // Archer Skills
  else if (className == "Archer")
  {
    meleeName = "Slice";
    magicName = "Poison Bomb";
    rangedName = "Pierce";
  }

  // Bard Skills
  else if (className == "Bard")
  {
      meleeName = "Slap";
      magicName = "Beg";
      rangedName = "Waft";
  }
}
